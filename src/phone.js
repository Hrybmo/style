var isGps = 1;
var Lat = "";
var Lng = "";
var inv = "";
var temp_units = "";
var isPersistanceUploaded = 0;
var apiKey = "df5992f787f04121486cd51dd9de74d9";

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

//https://www.dropbox.com/s/ikv406ftc4g2j5a/ChristmasTimeConfiguration1_2.html?dl=0
//---------------------------------------------------------
function GetStaticWeather()
{
  console.log("getting static weather");
  
  var url = "http://api.openweathermap.org/data/2.5/weather?lat=" +
      Lat + "&lon=" + Lng + "&appid=" + apiKey;
    // Send request to OpenWeatherMap
  console.log(url);
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
			console.log(json);
      // Temperature in K
      var temperature = json.main.temp;
      //console.log("Temperature is " + temperature);

      // Conditions
      var conditions = json.weather[0].main;      
      //console.log("Conditions are " + conditions);
      
      // Assemble dictionary using our keys
      var dictionary = {
        "KEY_TEMPERATURE": temperature,
        "KEY_CONDITIONS": conditions,
      };

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log("Weather info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
    }      
  );
}
//-----------------------------------------------------
function locationSuccess(pos) {
  // Construct URL
	var temperature = "";
	var conditions = "";
	var json;
  console.log("getting dynamic weather");
  
	var url = "http://api.openweathermap.org/data/2.5/weather?lat=" +
      pos.coords.latitude + "&lon=" + pos.coords.longitude + "&appid=" + apiKey;
	//console.log(url);
  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      json = JSON.parse(responseText);
			//console.log("response temp = " + responseText);
      // Temperature in K
      temperature = json.main.temp;
      //console.log("Temperature is -.js- " + temperature);

      // Conditions
      conditions = json.weather[0].main;      
      //console.log("Conditions are " + conditions);
			
			url = "http://api.openweathermap.org/data/2.5/forecast/daily?lat=" +
      pos.coords.latitude + "&lon=" + pos.coords.longitude + "&cnt=1&appid=" + apiKey;
			//console.log(url);
			// Send request to OpenWeatherMap
			xhrRequest(url, 'GET', 
				function(responseText2) {
					// responseText contains a JSON object with weather info
					json = JSON.parse(responseText2);
					//console.log("response temps = " + responseText);

					// Assemble dictionary using our keys
					var dictionary = {
						"KEY_TEMPERATURE": temperature,
						"KEY_CONDITIONS": conditions,
					};

					// Send to Pebble
					Pebble.sendAppMessage(dictionary,
					function(e) {
						console.log("Weather temp info sent to Pebble successfully!");
					},
					function(e) {
						console.log("Error sending weather temp info to Pebble!");
					}
					);
				}
			);
    }      
  );
}

function locationError(err) {
  console.log("Error requesting location!");
}
//------------------------------------------
function getWeather() {
  if(isGps == 1)
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
//--------------------------------------------------------
// Listen for when the watchface is opened
 
Pebble.addEventListener('ready', 
  function(e) {
    console.log("PebbleKit JS ready!");
    // Assemble dictionary using our keys
      var dictionary = {
        "KEY_JS_READY": 1
      };

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
      function(e) {
          console.log(e.type);
          console.log("JS ready sent to Pebble successfully!");
        },
        function(e) {
          console.log(e.type);
          console.log("Error sending JS ready to Pebble!");
        }
      );
  });
//-----------------------------------------------------
// weather or persistance data
Pebble.addEventListener('appmessage',
  function(e) {
     console.log(e.type);
     console.log("KEY_PERSISTANT_MESSAGE = " + e.payload.KEY_PERSISTANT_MESSAGE);
     console.log("KEY_WEATHER_MESSAGE = " + e.payload.KEY_WEATHER_MESSAGE);
     if(e.payload.KEY_PERSISTANT_MESSAGE == 1){
       isGps = e.payload.KEY_IS_GPS;
       //console.log("gps = " + isGps);
       Lat = e.payload.KEY_LATITUDE;
       Lng = e.payload.KEY_LONGITUDE;
       inv = e.payload.KEY_INVERT_UI;
       temp_units = e.payload.KEY_TEMP_UNITS;
       isPersistanceUploaded = 1;
     }
     if(e.payload.KEY_WEATHER_MESSAGE == 1){
         console.log("getting weather");
         getWeather();
     }
    
  }                    
);
//--------------------------------------------------------
Pebble.addEventListener("showConfiguration",
  function(e) {
    console.log(e.type);
    console.log("isPersistanceUploaded = " + isPersistanceUploaded);
    //if(isPersistanceUploaded){
       //https://www.dropbox.com/s/vcpv3nq31tqtnae/ChristmasTimeConfiguration1_2.html?dl=0
      /*
      var fullLink = (rawLink + "?" + "lat=" + Lat + "&lng=" + Lng + 
                     "&time_units=" + time_units + "&gps=" + gps + 
                     "&zip=" + zipCode + "&inv=" + inv + 
                     "&temp_units=" + temp_units);
      */
      //console.log(fullLink);
		//https://www.dropbox.com/s/4dztzi0xclwlflo/ChristmasTimeConfiguration1_3.html?dl=0
      Pebble.openURL("http://Hrybmo.github.io"); 
    //}
  }
);
//-----------------------------------------------------------
Pebble.addEventListener("webviewclosed",
  function(e) {
    var configuration = JSON.parse(decodeURIComponent(e.response));
    var dictionary = {"KEY_TEMP_UNITS": configuration.tempUnits,
                      "KEY_INVERT_UI": configuration.Background,
                      "KEY_IS_GPS" : configuration.isGPS,
                      "KEY_LATITUDE": configuration.latitude,
                      "KEY_LONGITUDE": configuration.longitude};
    
    console.log("Configuration window returned: " + JSON.stringify(configuration));
    //save locally too
    if(configuration.isGPS == "GPS"){
      isGps = 1;
    }
    else {
      isGps = 0;
    }
    
    Lat =  configuration.latitude;
    Lng =  configuration.longitude;
    inv =  configuration.Background;
    temp_units =  configuration.tempUnits;
    
    
    //Send to Pebble, persist there
    Pebble.sendAppMessage(dictionary,
      function(e) {
        console.log(e.type);
        console.log("Sending configuration data...");
        getWeather();
      },
      function(e) {
        console.log(e.type);
        console.log("configuration feedback failed!");
      }
    );
  }
);