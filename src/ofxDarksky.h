//
//  ofxForecastIO.h
//  ofxForecastIO
//
//  Created by Blair Neal on 9/6/16.
//
//

#include "ofMain.h"
#include "ofxJSON.h"
#include "WeatherData.h"

//API Docs are here: https://darksky.net/dev/docs

class ofxDarksky {
    
public:
    void setup(float _latitude, float _longitude, string _api_key);
    void update();
    void drawDebug();
    
    void requestUpdate();
    
    void parseWeather(ofBuffer buffer);
    void urlResponse(ofHttpResponse & response);
    void setNewLocation(float latitude, float longitude);
    
    void drawGraph(vector<float> vals, int min, int max, int locX, int locY);
    
    WeatherData* getWeatherData(); //if you just want the data reference
    WeatherData getWeatherDataCopy(); //if you want to copy the data elsewhere
    
private:
    string forecastURL;
    
    WeatherData weatherData;
    
    string APIKey;
    float latitude;
    float longitude;
    
    vector <float> prevTemps;
    vector <float> prevWinds;
    
    
    
};



