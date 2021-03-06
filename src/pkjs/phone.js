var gpsValue = 0;
var Lat = "";
var Lng = "";
var temp_units = "";
var isPersistanceUploaded = 0;
var apiKey = "df5992f787f04121486cd51dd9de74d9";
var userText = ""; //for weather text sense
var userText2 = ""; //for weather text sense

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

var locationOptions = {
  enableHighAccuracy: true, 
  maximumAge: 60000, 
  timeout: 15000
};
//---------------------------------------------------------
function GetStaticWeather()
{
  //console.log("getting static weather");
  var url = "http://api.openweathermap.org/data/2.5/weather?lat=" +
      Lat + "&lon=" + Lng + "&appid=" + apiKey;
    // Send request to OpenWeatherMap
  //console.log(url);
  xhrRequest(url, 'GET', sendWeatherDataBack); 
}
//-----------------------------------------------------
function locationSuccess(pos) {
  //console.log("getting dynamic weather");
	var url = "http://api.openweathermap.org/data/2.5/weather?lat=" +
      pos.coords.latitude + "&lon=" + pos.coords.longitude + "&appid=" + apiKey;
	//console.log(url);
  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', sendWeatherDataBack);      
}
//--------------------------------------------
function locationSave(pos){
	Lat = pos.coords.latitude;
	Lng = pos.coords.longitude;
	//console.log("lat = " + Lat);
	//console.log("lng = " + Lng);
  //console.log("its a " + typeof Lat);
	
	var dictionary = {"KEY_LATITUDE": String(Lat),
										"KEY_LONGITUDE": String(Lng)};
	//Send to Pebble, persist there
     Pebble.sendAppMessage(dictionary,
      function(e) {
        //console.log("Sending locationSave data...");
      },
      function(e) {
        console.log("locationSave data failed!");
      }
    );
	//console.log("location saved");
	getWeather();
}
//-----------------------------------
function sendWeatherDataBack(responseText){
		var temperature = "";
		var conditions = "";
		var json;
	   // responseText contains a JSON object with weather info
      json = JSON.parse(responseText);
			//console.log("response temp = " + responseText);
      // Temperature in K
      temperature = json.main.temp;
      //console.log("Temperature is -.js- " + temperature);

      // Conditions
      conditions = json.weather[0].icon;   
			var weatherDescription = json.weather[0].description;
			var text2 = "";
			var text1 = "";
			//if single line then keep at bottom
			if(weatherDescription.length <= 16){
				text2 = weatherDescription.substr(0,16);
				text1 = weatherDescription.substr(16,31);
			}
			else{
				text1 = weatherDescription.substr(0,16);
				text2 = weatherDescription.substr(16,31);
			}
			
			var dictionary;
			//console.log("weatherDescription - js = " + weatherDescription);
      if((userText === "") &&
				 (userText2 === "")){
				 dictionary = {
					"KEY_TEMPERATURE": temperature,
					"KEY_CONDITIONS": conditions,
					"KEY_USER_TEXT": text1,
					"KEY_USER_TEXT2": text2
     		 };
			}
			else{
				 dictionary = {
					"KEY_TEMPERATURE": temperature,
					"KEY_CONDITIONS": conditions
     		 };
			}

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
        function(e) {
          //console.log("Weather info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
}
//---------------------------------------------------
function locationError(err) {
  //console.log("Error requesting location!");
}
//------------------------------------------
function getWeather() {
  if(gpsValue === 0)
    {
        navigator.geolocation.getCurrentPosition(
        locationSuccess,
        locationError,
        locationOptions);
    }
  else //no gps use static
    {
      GetStaticWeather();
    }
}
//--------------------------------
function tryReadyAgain() {
	  var dictionary = {
        "KEY_JS_READY": 1
    };
	 Pebble.sendAppMessage(dictionary,null,
        function(e) {
          console.log(e.type);
				});
}
//--------------------------------------------------------
// Listen for when the watchface is opened
 
Pebble.addEventListener('ready', 
  function(e) {
    //console.log("PebbleKit JS ready!");
    // Assemble dictionary using our keys
      var dictionary = {
        "KEY_JS_READY": 1
      };

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,null,
        function(e) {
          console.log(e.type);
					setTimeout(tryReadyAgain,1000);
				}
     	);
 }
);
//-----------------------------------------------------
// weather or persistance data
Pebble.addEventListener('appmessage',
  function(e) {
     //console.log(e.type);
     //console.log("KEY_PERSISTANT_MESSAGE = " + e.payload.KEY_PERSISTANT_MESSAGE);
     //console.log("KEY_WEATHER_MESSAGE = " + e.payload.KEY_WEATHER_MESSAGE);
     if(e.payload.KEY_PERSISTANT_MESSAGE == 1){
       gpsValue = e.payload.KEY_IS_GPS;
       //console.log("gps = " + isGps);
       Lat = e.payload.KEY_LATITUDE;
       Lng = e.payload.KEY_LONGITUDE;
       temp_units = e.payload.KEY_TEMP_UNITS;
       isPersistanceUploaded = 1;
     }
     if(e.payload.KEY_WEATHER_MESSAGE == 1){
         //console.log("getting weather");
         getWeather();
     }
    
  }                    
);
//--------------------------------------------------------
Pebble.addEventListener("showConfiguration",
  function(e) {
    //console.log(e.type);
		Pebble.openURL("http://jjh4.host-ed.me/superDuper.com");
  }
);
//-----------------------------------------------------------
Pebble.addEventListener("webviewclosed",
  function(e) {
    var configuration = JSON.parse(decodeURIComponent(e.response));
    var dictionary = {"KEY_TEMP_UNITS": configuration.tempUnits,
                      "KEY_IS_GPS" : configuration.isGPS,
											"KEY_USER_TEXT": configuration.userText,
											"KEY_USER_TEXT2": configuration.userText2,
											"KEY_BACK_COLOR": configuration.backgroundColor,
											"KEY_FORE_COLOR": configuration.foregroundColor,
											"KEY_TEXT_COLOR": configuration.textColor
										 };
    
    //console.log("Configuration window returned: " + JSON.stringify(configuration));
    //save locally too
		userText = configuration.userText;
		userText2 = configuration.userText2;
    
    //Send to Pebble, persist there
    Pebble.sendAppMessage(dictionary,
      function(e) {
        //console.log(e.type);
        //console.log("Sending configuration data...");
      },
      function(e) {
        //console.log(e.type);
        console.log("configuration feedback failed!");
      }
    );
		gpsValue = configuration.isGPS;
    if(gpsValue == 1){
			//get a gps reading to save
			navigator.geolocation.getCurrentPosition(locationSave,locationError,locationOptions);
    }
		else{
			getWeather();
		}
  }
);