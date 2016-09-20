//
//  ofxDarksky.cpp
//  ofxDarksky
//
//  Created by Blair Neal on 9/6/16.
//
//

#include "ofxDarksky.h"


void ofxDarksky::setup(float _lat, float _longitude, string _api_key){
    ofRegisterURLNotification(this);
    APIKey = _api_key; //need to read this in as a value from an XML or JSON, don't store in code
    latitude = _lat;
    longitude = _longitude; //Address of 45 Main St.
    
    forecastURL = "https://api.darksky.net/forecast/"+ APIKey + "/" + ofToString(latitude)+","+ofToString(longitude);
    cout<<"Setup Pinging: "<<forecastURL<<endl;
    ofLoadURLAsync(forecastURL, "weather");
    
    
}


void ofxDarksky::urlResponse(ofHttpResponse & response){
    
    if(response.request.name == "weather")
    {
        parseWeather(response.data);
    }
}

void ofxDarksky::parseWeather(ofBuffer buffer)
{
    ofLog(OF_LOG_VERBOSE)<<"parseWeather"<<endl;
    
    ofxJSONElement weather;
    if(weather.parse(buffer))
    {
        weatherData.setCurrentTemp(weather["currently"]["temperature"].asFloat());
        weatherData.setCurrentWindBearing(weather["currently"]["windBearing"].asFloat());
        weatherData.setCurrentWindSpeed(weather["currently"]["windSpeed"].asFloat());
        weatherData.setCurrentHumidity(weather["currently"]["humidity"].asFloat());
        weatherData.setCurrentDewPoint(weather["currently"]["dewPoint"].asFloat());
        weatherData.setCurrentCloudCover(weather["currently"]["cloudCover"].asFloat());
        weatherData.setCurrentVisibility(weather["currently"]["visibility"].asFloat());
        weatherData.setCurrentPressure(weather["currently"]["pressure"].asFloat());
        weatherData.setCurrentNearStormDistance(weather["currently"]["nearestStormDistance"].asFloat());
        weatherData.setCurrentPrecipIntensity(weather["currently"]["precipIntensity"].asFloat());
        weatherData.setCurrentPrecipProbability(weather["currently"]["precipProbability"].asFloat());
        weatherData.setCurrentTimeZone(weather["timezone"].asString());
        weatherData.setCurrentSummary(weather["currently"]["summary"].asString());
        prevTemps.push_back(weatherData.getCurrentTempF());
        prevWinds.push_back(weatherData.getCurrentWindSpeed());
    }
    
    if(prevTemps.size()>20){
        prevTemps.erase(prevTemps.begin(), prevTemps.begin()+1);
    }
    if(prevWinds.size()>20){
        prevWinds.erase(prevWinds.begin(), prevWinds.begin()+1);
    }
}

void ofxDarksky::drawDebug(){
    ofSetColor(255);
    string output = "Current Weather at " + ofToString(latitude) + " " + ofToString(longitude) + "\n\n";
    
    output +=   "Summary: " + weatherData.getCurrentSummary() +"\n";
    output +=   "Current Temp: " + ofToString(weatherData.getCurrentTempF()) + "\n";
    output +=   "Current Wind Speed: " + ofToString(weatherData.getCurrentWindSpeed()) + "\n";
    output +=   "Current Wind Bearing Angle: " + ofToString(weatherData.getCurrentWindBearing()) + "\n";
    output +=   "Current Wind Bearing Word: " + weatherData.getCurrentWindBearingString() + "\n";
    output +=   "Current Humidity: " + ofToString(weatherData.getCurrentHumidity()) + "\n";
    output +=   "Current DewPoint: " + ofToString(weatherData.getCurrentDewPoint()) + "\n";
    output +=   "Current DewPoint Descript: " + weatherData.getCurrentDewPointString() + "\n";
    output +=   "Current Pressure: " + ofToString(weatherData.getCurrentPressure()) + "\n";
    output +=   "Current Cloud Cover: " + ofToString(weatherData.getCurrentCloudCover()) + "\n";
    output +=   "Current Visibility: " + ofToString(weatherData.getCurrentVisibility()) + "\n";
    output +=   "Current PrecipIntensity: " + ofToString(weatherData.getCurrentPrecipIntensity()) + "\n";
    output +=   "Current PrecipProbability: " + ofToString(weatherData.getCurrentPrecipProbability()) + "\n";
    output +=   "Current Precip Description: " + ofToString(weatherData.getCurrentPrecipIntensityString()) + "\n";
    output +=   "Current Near Storm Dist.: " + ofToString(weatherData.getCurrentNearStormDistance()) + "\n";
    
    ofDrawBitmapString(output, 20,60);
    
    ofDrawBitmapString(prevTemps, 300,520);
    ofDrawBitmapString(prevWinds, 300,670);
    
    //Draw Wind Compass
    
    ofPushMatrix();
    ofTranslate(100, 600);
    ofDrawBitmapString("Wind Direction\nN is Up",-50,60);
    int maxDim = 50;
    ofDrawLine(0, 0, 2*maxDim, 0);
    ofDrawLine(maxDim, -maxDim, maxDim, maxDim);
    float scaleWindSpeed = ofMap(weatherData.getCurrentWindSpeed(), 0,30,0,50,true);
    float windVecX = maxDim-scaleWindSpeed*sin(ofDegToRad(weatherData.getCurrentWindBearing())-PI);
    float windVecY = scaleWindSpeed*cos(ofDegToRad(weatherData.getCurrentWindBearing())-PI);
    ofDrawCircle(windVecX,windVecY, 3);
    ofDrawLine(maxDim, 0, windVecX, windVecY);
    
    //ofDrawCircle(50+50*sin(ofDegToRad(50*ofGetElapsedTimef())-PI), 50*cos(ofDegToRad(50*ofGetElapsedTimef())-PI), 3);
    ofPopMatrix();
    
    //draw history of temperatures and wind
    ofSetColor(255,127,100);
    drawGraph(prevTemps, 0, 110,300,500);
    ofSetColor(127,255,127);
    drawGraph(prevWinds, 0,30,300,650);
    
}

void ofxDarksky::drawGraph(vector<float> vals, int min, int max, int locX, int locY){
    
  
    ofPushMatrix();
    ofTranslate(locX, locY);
    ofBeginShape();
    ofVertex(0,0);
    for(int i=0; i<vals.size(); i++){
        ofVertex(i*20, ofMap(vals[i], min, max, 0,-100));
    }
    if(vals.size()>0){
        ofVertex((vals.size())*20-20, 0);
    }
    ofEndShape();
    
    ofSetColor(255);
    for(int i=0; i<vals.size(); i++){
        ofDrawCircle(i*20, ofMap(vals[i], min, max, 0,-100), 5);
    }
    ofDrawLine(0,0,20*20-20,0);
    ofDrawLine(0,-100,20*20-20,-100);
    ofPopMatrix();
}

void ofxDarksky::setNewLocation(float _latitude, float _longitude){
    
    //make sure the ranges are in proper values...
    latitude = _latitude;
    latitude = ofClamp(latitude,-90,90);
    longitude = _longitude;
    longitude = ofClamp(longitude, -180,180);
    
}

void ofxDarksky::requestUpdate(){
    //Be careful about how often you ping the API for updates! You only get 1000 API requests a day in the free tier - so if you're running this for 12 hours a day, you can ask for an update about once every minute to stay safely within the limit (12*60 = 720)
    forecastURL = "https://api.darksky.net/forecast/"+ APIKey + "/" + ofToString(latitude)+","+ofToString(longitude);
    ofLog()<<"Pinging: "<<forecastURL<<endl;
    ofLoadURLAsync(forecastURL, "weather");
}

WeatherData* ofxDarksky::getWeatherData(){
    return &weatherData;
}

WeatherData ofxDarksky::getWeatherDataCopy(){
    return weatherData;
}