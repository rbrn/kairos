
var _Debug = false;  // settare questo valore a "false" per disattivare il debbuging.

// Definizione codice eccezione/errore
var _NoError = 0;
var _GeneralException = 101;
var _ServerBusy = 102;
var _InvalidArgumentError = 201;
var _ElementCannotHaveChildren = 202;
var _ElementIsNotAnArray = 203;
var _NotInitialized = 301;
var _NotImplementedError = 401;
var _InvalidSetValue = 402;
var _ElementIsReadOnly = 403;
var _ElementIsWriteOnly = 404;
var _IncorrectDataType = 405;

// definizione variabili locali
var apiHandle = null;
var API = null;
var findAPITries = 0;


/*******************************************************************************
**
** Function: doLMSInitialize()
** Inputs:  None
** Return:  CMIBoolean true se l'inizializzazione ha avuto successo, o
**          CMIBoolean false se l'inizializzazione è fallita.
**
** Descrizione:
** Inizializza la comunicazione con LMS chiamando la funzione LMSInitialize
** che sarà implementata dall'LMS.
**
*******************************************************************************/
function doLMSInitialize()
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSInitialize was not successful.");
      return "false";
   }

   var result = api.LMSInitialize("");

   if (result.toString() != "true")
   {
      var err = ErrorHandler();
   }

   return result.toString();
}

/*******************************************************************************
**
** Function doLMSFinish()
** Inputs:  None
** Return:  CMIBoolean true se ha avuto successo
**          CMIBoolean false se è fallita.
**
** Descrizione:
** Chiude la comunicazione con LMS chiamando la funzione LMSFinish
** che sarà implentata dall'LMS
**
*******************************************************************************/
function doLMSFinish()
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSFinish was not successful.");
      return "false";
   }
   else
   {
      var result = api.LMSFinish("");
      if (result.toString() != "true")
      {
         var err = ErrorHandler();
      	alert("err=" + err)
      }

   }

   return result.toString();
}

/*******************************************************************************
**
** Function doLMSGetValue(name)
** Inputs:  name - Stringa che rappresenta la categoria o l'elemento definiti nel cmi data model 
**          (es.: cmi.core.student_id)
** Return:  Ritorna il valore attualmente assegnato dall'LMS all'elemento del cmi data model
**          definito dall'elemento o categoria identificato dal nome del valore in input.
**
** Descrizione:
** Confeziona la chiamata al metodo LMSGetValue.
**
*******************************************************************************/
function doLMSGetValue(name)
{
   var api = getAPIHandle();
   if (api == null)
   {
     // alert("Unable to locate the LMS's API Implementation.\nLMSGetValue was not successful.");
      return "";
   }
   else
   {
      var value = api.LMSGetValue(name);
      var errCode = api.LMSGetLastError().toString();
      if (errCode != _NoError)
      {
         // si è verificato un errore e visualizza la descrizione dell'errore
         var errDescription = api.LMSGetErrorString(errCode);
         alert("LMSGetValue("+name+") failed. \n"+ errDescription);
         return "";
      }
      else
      {
         
         return value.toString();
      }
   }
}

/*******************************************************************************
**
** Function doLMSSetValue(name, value)
** Inputs:  name - stringa che rappresenta la categoria o l'elemento definiti nel cmi data model
**          value - valore assegnato al nome dell'elemento o categoria
** Return:  CMIBoolean true se ha avuto successo
**          CMIBoolean false se è fallita.
**
** Descrizione:
** Confeziona la chiamata al metodo LMSSetValue.
**
*******************************************************************************/
function doLMSSetValue(name, value)
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSSetValue was not successful.");
      return;
   }
   else
   {
      var result = api.LMSSetValue(name, value);
	  var errCode = api.LMSGetLastError().toString();
	  if (errCode != _NoError)
      {
         // si è verificato un errore e visualizza la descrizione dell'errore
         var errDescription = api.LMSGetErrorString(errCode);
         alert("LMSSetValue("+name+","+value+") failed. \n"+ errDescription);
         return "";
      }
	
      if (result.toString() != "true")
      {
         var err = ErrorHandler();
      }
   }

   return;
}

/*******************************************************************************
**
** Function doLMSCommit()
** Inputs:  None
** Return:  None
**
** Descrizione:
** Chiama la funzione LMSCommit
**
*******************************************************************************/
function doLMSCommit()
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSCommit was not successful.");
      return "false";
   }
   else
   {
      var result = api.LMSCommit("");
      if (result != "true")
      {
         var err = ErrorHandler();
      }
	 
   }

   return result.toString();
}

function doLMSCommitFinish()
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSCommit was not successful.");
      return "false";
   }
   else
   {
   /*
      var result = api.LMSCommit("");
      if (result != "true")
      {
         var err = ErrorHandler();
      }
	 */ 
	  var result = api.LMSFinish("");
      if (result.toString() != "true")
      {
         var err = ErrorHandler();
      	alert("err=" + err)
      }
	  
   }

   return result.toString();
}
/*******************************************************************************
**
** Function doLMSGetLastError()
** Inputs:  None
** Return:  Codice di errore settato dall'ultima chiamata di funzione da parte dell'LMS.
**
** Descrizione:
** Chiama la funzione LMSGetLastError
**
*******************************************************************************/
function doLMSGetLastError()
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSGetLastError was not successful.");
      //ritorna un general error nel caso in cui non è possibile ricavare un codice ben definito
      return _GeneralError;
   }

   return api.LMSGetLastError().toString();
}

/*******************************************************************************
**
** Function doLMSGetErrorString(errorCode)
** Inputs:  errorCode - codice d'errore
** Return:  descrizione testuale corrispondente al codice di errore in input
**
** Descrizione:
** Chiama la funzione LMSGetErrorString
**
********************************************************************************/
function doLMSGetErrorString(errorCode)
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSGetErrorString was not successful.");
   }

   return api.LMSGetErrorString(errorCode).toString();
}

/*******************************************************************************
**
** Function doLMSGetDiagnostic(errorCode)
** Inputs:  errorCode - codice d'errore (formato integer ), o null
** Return:  specifica descrizione testuale dell'autore 
** corrispondente al codice di errore (personalizzato) in input
**
** Descrizione:
** Chiama la funzione LMSGetDiagnostic
**
*******************************************************************************/
function doLMSGetDiagnostic(errorCode)
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nLMSGetDiagnostic was not successful.");
   }

   return api.LMSGetDiagnostic(errorCode).toString();
}

/*******************************************************************************
**
** Function LMSIsInitialized()
** Inputs:  none
** Return:  true se l'LMS API è attualmente inizializzata, altrimenti false
**
** Descrizione:
** Determina se l'LMS API è attualmente inizializzata o no.
**
*******************************************************************************/
function LMSIsInitialized()
{
   var api = getAPIHandle();
   if (api == null)
   {
      alert("Unable to locate the LMS's API Implementation.\nLMSIsInitialized() failed.");
      return false;
   }
   else
   {
      var value = api.LMSGetValue("cmi.core.student_name");
      var errCode = api.LMSGetLastError().toString();
      if (errCode == _NotInitialized)
      {
         return false;
      }
      else
      {
         return true;
      }
   }
}

/*******************************************************************************
**
** Function ErrorHandler()
** Inputs:  None
** Return:  valore corrente del codice d'errore
**
** Descrizione:
** Determina se si è verificato un errore nella precedente chiamata API, e in tal caso, 
** visualizza un messaggio all'utente. Se al codice d'errore è associato del testo,
** visualizza anch'esso.
**
*******************************************************************************/
function ErrorHandler()
{
   var api = getAPIHandle();
   if (api == null)
   {
      //alert("Unable to locate the LMS's API Implementation.\nCannot determine LMS error code.");
      return;
   }

   // check di errori
   var errCode = api.LMSGetLastError().toString();
   if (errCode != _NoError)
   {
      // si è verificato un errore, ne visualizza la descrizione
      var errDescription = api.LMSGetErrorString(errCode);

      if (_Debug == true)
      {
         errDescription += "\n";
         errDescription += api.LMSGetDiagnostic(null);
      }

      alert(errDescription);
   }

   return errCode;
}

/******************************************************************************
**
** Function getAPIHandle()
** Inputs:  None
** Return:  valore contenuto dall'APIHandle
**
** Descrizione:
** Ritorna l'handle all'oggetto API se è stato precedentemente settato
** altrimenti ritorna null
**
*******************************************************************************/
function getAPIHandle()
{
   if (apiHandle == null)
   {
      apiHandle = getAPI();
   }

   return apiHandle;
}


/*******************************************************************************
**
** Function findAPI(win)
** Inputs:  win - un oggetto Window
** Return:  un API object, se trovato, altrimenti null
**
** Descrizione:
** Questa funzione cerca un oggetto chiamato API nelle finestre parent e opener
**
*******************************************************************************/
function findAPI(win)
{
   while ((win.API == null && win.API_1484_11 == null) && (win.parent != null) && (win.parent != win))
   {
      findAPITries++;
      // Nota: 7 è un numero arbitrario, ma potrebbe essere più che sufficiente
      if (findAPITries > 7) 
      {
         //alert("Error finding API -- too deeply nested.");
         return null;
      }
      
      win = win.parent;

   }
   if (win.API != null) {
   		return win.API;
   } else {
   		return win.API_1484_11;
   }
}



/*******************************************************************************
**
** Function getAPI()
** Inputs:  none
** Return:  un API object, se trovato, altrimenti null
**
** Descrizione:
** Questa funzione cerca un oggetto chiamato API, prima nella corrente gerarchia dei frame
** della finestra e poi, se necessario, nella corrente gerarchia delle finestre opener della 
** finestra (se esiste una finestra opener).
**
*******************************************************************************/
function getAPI()
{
   var theAPI = findAPI(window);
   if ((theAPI == null) && (window.opener != null) && (typeof(window.opener) != "undefined"))
   {
      theAPI = findAPI(window.opener);
   }
   if (theAPI == null)
   {
      //alert("Unable to find an API adapter");
   }
   return theAPI
}
