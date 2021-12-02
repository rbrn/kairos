import java.io.{FileInputStream, PrintWriter}
import java.io._

object KairosSource {

  import java.io.File

  def getVariableNameFromLine(s: String): String = {
    var str = s.split("=")(0)
    if (str.contains("while"))
      str = str.split("\\(")(1)
    return str.trim.replaceAll("\t", "")
  }

  def workWithThisFiles(file: File) {
    file.setWritable(true);
    print("processing file: " + file.getAbsoluteFile + "\n")

    var source = scala.io.Source.fromFile( file, "ISO-8859-1");
    var queryVar, resultVar, fetchVar, numRowVar = None: Option[String];
    val writer = new PrintWriter(new File("temp"));
    for (line <- source.getLines()) {
      if (line.contains("SELECT") || line.contains("UPDATE") || line.contains("INSERT")  || line.contains("DELETE")
        || (line.contains("select") && line.contains("FROM") )) {
        queryVar = Some(getVariableNameFromLine(line));

        resultVar = None: Option[String];
        fetchVar = None: Option[String];
        numRowVar = None: Option[String];
        if(line.contains("mysql_query")){
          val newline = line.replace(" ", "").replace("mysql_query",  "$mysqli->query("+queryVar.get+")");
          writer.append(newline + "\n");
        } else {
          writer.append(line + "\n");
        }
      } else if (queryVar != None && line.contains("mysql_query")) {
        resultVar = Some(getVariableNameFromLine(line));
        val replacePatt =
          if (line.contains("$db")) {
            "mysql_query("+queryVar.get+",$db)";
          } else {
            "mysql_query("+queryVar.get+")"
          }
        val newline = line.replace(" ", "").replace(replacePatt.toString,  "$mysqli->query("+queryVar.get+")");
        writer.append(newline + "\n");
      } else if (resultVar != None && line.contains("mysql_fetch_array")) {
        fetchVar = Some(getVariableNameFromLine(line));
        val newline = line.replace("mysql_fetch_array(" + resultVar.get + ")", resultVar.get + "->fetch_array()")
        writer.append(newline + "\n");
      }else if (resultVar != None && line.contains("mysql_num_rows")) {
        val newline = line.replace("mysql_num_rows(" + resultVar.get + ")", resultVar.get + "->num_rows")
        writer.append(newline + "\n");
      }else if (line.contains("mysql_insert_id()")) {
        val newline = line.replace("mysql_insert_id()", "$mysqli->insert_id")
        writer.append(newline + "\n");
      }
      else {
        writer.append(line + "\n");
      }
    }

    writer.close();
    copy(new File("temp"), file)
  }


  @throws(classOf[IOException])
  def copy(from: File, to: File) {
    use(new FileInputStream(from)) { in =>
      use(new FileOutputStream(to)) { out =>
        val buffer = new Array[Byte](1024)
        Iterator.continually(in.read(buffer))
          .takeWhile(_ != -1)
          .foreach { out.write(buffer, 0 , _) }
      }
    }
  }

  def use[T <: { def close(): Unit }](closable: T)(block: T => Unit) {
    try {
      block(closable)
    }
    finally {
      closable.close()
    }
  }

  def main(args: Array[String]) {
    var sourceDirectory = new File("C:\\wamp\\www\\kairos");
    val phpFiles = findFiles(_.getName endsWith ".php")(sourceDirectory)
    phpFiles.foreach(e => workWithThisFiles(e))
    val incFiles = findFiles(_.getName endsWith ".inc")(sourceDirectory)
    incFiles.foreach(e => workWithThisFiles(e))
  }

  def findFiles(fileFilter: (File) => Boolean = (f) => true)(f: File): List[File] = {
    val ss = f.list()
    val list = if (ss == null) {
      Nil
    } else {
      ss.toList.sorted
    }
    val visible = list.filter(_.charAt(0) != '.')
    val these = visible.map(new File(f, _))
    these.filter(fileFilter) ++ these.filter(_.isDirectory).flatMap(findFiles(fileFilter))
  }
}