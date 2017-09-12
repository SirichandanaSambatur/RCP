var myFunction;

function myFunction(d) {
 
   $(d).toggle();

}

$(document).ready(function(d){

	myFunction =function (d){

$("#"+d).toggle();
}

});