function nota(newURL, newName, newFeatures, orgName) {
  var remote = open(newURL, newName, newFeatures);
  if (remote.opener == null)
    remote.opener = window;
  remote.opener.name = orgName;
  return remote;
}