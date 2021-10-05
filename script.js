fetch("http://ilias/data.json")
  .then((response) => response.json())
  .then((data) => console.log(data));

$(document).ready(function () {
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
      student += "</tr>";
    });

    //INSERTING ROWS INTO TABLE
    $("#test").append(student);
  });
});
