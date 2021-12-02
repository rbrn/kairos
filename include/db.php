<?php
class DB
{
	var $Host = K_DB_HOST;			
	var $Database = K_DB_NAME;		
	var $User = K_DB_USER;			
	var $Password = K_DB_PASS;		
	var $Persistent = K_USE_PERSISTENT;	
	var $Link_ID = 0;				
	var $Query_ID = 0;				
	var $Record	= array();			
	var $Row;						
	var $Errno = 0;					
	var $Error = "";

	function halt($msg)
	{
		echo("</TD></TR></TABLE><B>Database error:</B> $msg<BR>\n");
		echo("<B>MySQL error</B>: $this->Errno ($this->Error)<BR>\n");
		die("Session halted.");
	}

	function connect()
	{
		if($this->Link_ID == 0)
		{
			if ($this->Persistent)
			{
				$this->Link_ID = mysql_pconnect($this->Host, $this->User, $this->Password);
			}
			else
			{
				$this->Link_ID = mysql_connect($this->Host, $this->User, $this->Password);
			};
			if (!$this->Link_ID)
			{
				$this->halt("Link_ID == false, connect failed");
			}
			$SelectResult = mysql_select_db($this->Database, $this->Link_ID);
			if(!$SelectResult)
			{
				$this->Errno = mysql_errno($this->Link_ID);
				$this->Error = mysql_error($this->Link_ID);
				$this->halt("cannot select database <I>".$this->Database."</I>");
			}
		}
	}

	function query($Query_String)
	{
		$this->connect();
		$this->Query_ID = mysql_query($Query_String,$this->Link_ID);
		$this->Row = 0;
		$this->Errno = mysql_errno();
		$this->Error = mysql_error();
		if (!$this->Query_ID)
		{
			$this->halt("Invalid SQL: ".$Query_String);
		}
		return $this->Query_ID;
	}

	function next_record()
	{
		$this->Record = mysql_fetch_array($this->Query_ID);
		$this->Row += 1;
		$this->Errno = mysql_errno();
		$this->Error = mysql_error();
		$stat = is_array($this->Record);
		if (!$stat)
		{
			mysql_free_result($this->Query_ID);
			$this->Query_ID = 0;
		}
		return $this->Record;
	}

	function num_rows()
	{
		return mysql_num_rows($this->Query_ID);
	}

	function optimize($tbl_name)
	{
		$this->connect();
		$this->Query_ID = @mysql_query("OPTIMIZE TABLE $tbl_name",$this->Link_ID);
	}

	function clean_results()
	{
		if($this->Query_ID != 0) mysql_freeresult($this->Query_ID);
	}

	function close()
	{
		if($this->Link_ID != 0 && !$this->Persistent) mysql_close($this->Link_ID);
	}
}
?>
