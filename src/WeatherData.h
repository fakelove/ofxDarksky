
#include "ofMain.h"

//This is mostly a data container and slight manipulation object. HTTP calls and handling should be handled by its container

//Wanted to keep the data storage seperate from the other class, even if this is a bit verbose
class WeatherData {
private:
    float currentTemperature;
    float currentWindBearing;
    float currentWindSpeed;
    float currentCloudCover;
    float currentPressure;
    float currentVisibility;
    float currentNearStormDistance;
    float currentPrecipIntensity;
    float currentPrecipProbability;
    string currentSummary;
    float currentHumidity;
    float currentDewPoint;
    string currentTimeZone;
    
public:
    
    //TODO: seperate setters into private, just in case...
    
    WeatherData(){
        currentTemperature = 0;
        currentWindBearing = 0;
        currentWindSpeed = 0;
        currentCloudCover = 0;
        currentPressure = 0;
        currentVisibility = 0;
        currentNearStormDistance = 0;
        currentPrecipIntensity = 0;
        currentPrecipProbability = 0;
        string weatherSummary = "it sure is weathery outside";
        string currentTimezone = "EST";
        currentHumidity = 0;
        currentDewPoint = 0;
    }
    
    void setCurrentTemp(float temp){
        //No method for setting as C, API returns F
        currentTemperature = temp;
    }
    
    float getCurrentTempF(){ //Fahrenheit..
        return currentTemperature;
    }
    
    float getCurrentTempC(){ //Celsius
        float celsiusConv = (currentTemperature-32)/1.8;
        return celsiusConv;
    }
    
    void setCurrentWindSpeed(float windSpeed){
        currentWindSpeed = windSpeed;
    }
    
    float getCurrentWindSpeed(){ //In MPH
        return currentWindSpeed;
    }
    
    void setCurrentWindBearing(float windBearing){
        currentWindBearing = windBearing;
    }
    
    float getCurrentWindBearing(){ //In Degrees - North being 0
        return currentWindBearing;
    }
    
    string getCurrentWindBearingString(){ //In Degrees - North being 0 and going clockwise from there
        
        string direction = "";
        
        //Each direction has 45 degrees of freedom...not getting fine grained with NNW and stuff, fuck that
        if(currentWindBearing>=337.5 || currentWindBearing<22.5){
            direction = "North";
        }else if(currentWindBearing>=22.5 && currentWindBearing<67.5){
            direction = "North East";
        }else if(currentWindBearing>=67.5 && currentWindBearing<112.5){
            direction = "East";
        }else if(currentWindBearing>=112.5 && currentWindBearing<157.5){
            direction = "South East";
        }else if(currentWindBearing>=157.5 && currentWindBearing<202.5){
            direction = "South";
        }else if(currentWindBearing>=202.5 && currentWindBearing<247.5){
            direction = "South West";
        }else if(currentWindBearing>=247.5 && currentWindBearing<292.5){
            direction = "West";
        }else if(currentWindBearing>=292.5 && currentWindBearing<337.5){
            direction = "North West";
        }else{
            direction = "";
        }
        
        return direction;
        
    }
    
    void setCurrentCloudCover(float cloudCover){
        currentCloudCover = cloudCover;
    }
    
    float getCurrentCloudCover(){ //Percentage
        return currentCloudCover;
    }
    
    void setCurrentVisibility(float visibility){
        currentVisibility = visibility;
    }
    
    float getCurrentVisibility(){ //In Miles
        return currentVisibility;
    }
    
    void setCurrentHumidity(float humidity){
        currentHumidity = humidity;
    }
    
    float getCurrentHumidity(){
        return currentHumidity;
    }
    
    void setCurrentDewPoint(float dewP){
        currentDewPoint = dewP;
    }
    
    float getCurrentDewPoint(){ //in Farenheit
        return currentDewPoint;
    }
    
    string getCurrentDewPointString(){
        //Just took comfort levels from here: http://2.bp.blogspot.com/_5e3pXsJ01wE/TDXJPOB-JUI/AAAAAAAACV4/BucabX5NBeI/s1600/Brian_Blog.JPG
        //Although these should also be related to relative humidity and actual temp too, but i didn't find a good conversion to "feel"
        string humidDescriptor = "";
        
        if(currentPrecipIntensity<55){
            humidDescriptor = "Pleasant";
        }else if(currentPrecipIntensity>=55 && currentPrecipIntensity<60){
            humidDescriptor = "Comfortable";
        }else if(currentPrecipIntensity>=60 && currentPrecipIntensity<65){
            humidDescriptor = "Sticky";
        }else if(currentPrecipIntensity>=65 && currentPrecipIntensity<70){
            humidDescriptor = "Uncomfortable";
        }else if(currentPrecipIntensity>=70 && currentPrecipIntensity<75){
            humidDescriptor = "Oppressive";
        }else if(currentPrecipIntensity>=75){
            humidDescriptor = "Miserable";
        }else{
            humidDescriptor = "";
        }
        
        return humidDescriptor;
        
    }
    
    void setCurrentPressure(float pressure){
        currentPressure = pressure;
    }
    
    float getCurrentPressure(){ //In Mb
        return currentPressure;
    }
    
    void setCurrentNearStormDistance(float nearStormDistance){
        currentNearStormDistance = nearStormDistance;
    }
    
    float getCurrentNearStormDistance(){ //Miles away
        return currentNearStormDistance;
    }
    
    void setCurrentPrecipIntensity(float precipIntensity){

        currentPrecipIntensity = precipIntensity;
    }
    
    float getCurrentPrecipIntensity(){
        return currentPrecipIntensity;
    }
    
    string getCurrentPrecipIntensityString(){
        
        //A numerical value representing the average expected intensity (in inches of liquid water per hour) of precipitation occurring at the given time conditional on probability (that is, assuming any precipitation occurs at all). A very rough guide is that a value of 0 in./hr. corresponds to no precipitation, 0.002 in./hr. corresponds to very light precipitation, 0.017 in./hr. corresponds to light precipitation, 0.1 in./hr. corresponds to moderate precipitation, and 0.4 in./hr. corresponds to heavy precipitation
        string rainDescriptor = "";
        
        if(currentPrecipIntensity<0.002){
            rainDescriptor = "No Precipitation";
        }else if(currentPrecipIntensity>=0.002 && currentPrecipIntensity<0.017){
                rainDescriptor = "Drizzle";
        }else if(currentPrecipIntensity>=0.017 && currentPrecipIntensity<0.1){
            rainDescriptor = "Light Rain";
        }else if(currentPrecipIntensity>=0.1 && currentPrecipIntensity<0.4){
            rainDescriptor = "Moderate Rain";
        }else if(currentPrecipIntensity>=0.4){
            rainDescriptor = "Heavy Rain";
        }else{
            rainDescriptor = "";
        }
        
        return rainDescriptor;
    }
    
    void setCurrentPrecipProbability(float precipProb){
        currentPrecipProbability = precipProb;
    }
    
   float getCurrentPrecipProbability(){
        return currentPrecipProbability;
    }
    
    void setCurrentSummary(string _summary){
        currentSummary = _summary;
    }
    
    string getCurrentSummary(){
        return currentSummary;
    }
    
    void setCurrentTimeZone(string _timeZone){
        currentTimeZone = _timeZone;
    }
    
    string getCurrentTimeZone(){
        return currentTimeZone;
    }
    
    
};