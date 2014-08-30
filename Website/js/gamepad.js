var hasGP = false;
var repGP;

function canGame() {
  return "getGamepads" in navigator;
}

function sendGamepadData(){
  var gp = navigator.getGamepads()[0];
  var sendData = JSON.stringify({leftStick: gp.axes["LEFT_ANALOGUE_VERT"], rightStick: gp.axes["RIGHT_ANALOGUE_VERT"]});
  $.ajax({
    url: '/node_eats',
    data: sendData,
    type: 'POST',
    dataType: 'json',
    success: function(data){
      console.log(data);
    }
  }).done(function(){
    console.log("done!");
  });

}

