fetch("http://ilias/data.json")
  .then((response) => response.json())
  .then((data) => tableG(data));


function tableG(data) {
  var student = "";
  let table = document.getElementById("test")


  for (let element of data) {
    let row = table.insertRow();
    for (key in element) {
      let cell = row.insertCell();
      let text = document.createTextNode(element[key]);
      cell.appendChild(text);
    }
  }
}

/*$(document).ready(function () {
  // FETCHING DATA FROM JSON FILE
  $.getJSON("http://ilias/data.json", function (data) {
    var student = "";

    // ITERATING THROUGH OBJECTS
    $.each(data, function (key, value) {
      //CONSTRUCTION OF ROWS HAVING
      // DATA FROM JSON OBJECT
      student += "<tr>";
      student += "<td>" + value.name + "</td>";

      student += "<td>" + value.dink + "</td>";
      student += "<td>" + value.time + "</td>";
      student += "</tr>";
    });

    //INSERTING ROWS INTO TABLE
    $("#test").append(student);
  });
});*/

function setCookie(cname, cvalue, exdays) {
  const d = new Date();
  d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
  let expires = "expires=" + d.toUTCString();
  document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function checkCookie() {
  let user = getCookie("username");
  if (user != "") {
    alert("Welcome again " + user);
    document.getElementById("cookie").value=user;
  } else {
    user = prompt("Please enter your name:", "");
    if (user != "" && user != null) {
      setCookie("username", user, 30);
    }
  }
}

function getCookie(cname) {
  let name = cname + "=";
  let ca = document.cookie.split(';');
  for (let i = 0; i < ca.length; i++) {
    let c = ca[i];
    while (c.charAt(0) == ' ') {
      c = c.substring(1);
    }
    if (c.indexOf(name) == 0) {
      return c.substring(name.length, c.length);
    }
  }
  return "";
}


