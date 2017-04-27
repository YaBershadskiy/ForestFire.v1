using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Threading.Tasks;
using System.Xml;
using ForestFires.Models;

namespace ForestFires.Services
{
    public static class Weather
    {
       
        public static WeatherData GetWeatherFromSiteToday()
        {
            XmlDocument doc1;
            XmlElement xRoot;
            XmlNode xNode;

            WeatherData weather = new WeatherData();
            doc1 = new XmlDocument();
            doc1.Load(@"http://www.yr.no/place/Ukraine/Kharkiv/Kharkiv/forecast.xml");

            xRoot = doc1.DocumentElement;
            xNode = xRoot.ChildNodes[0];
            weather.City = xNode["name"].InnerText;

          

            xNode = xRoot.ChildNodes[5];
            XmlNode xNode1 = xNode.ChildNodes[0];
            xNode1 = xNode1.ChildNodes[0];
            XmlNode period = xNode1.Attributes.GetNamedItem("period");

            XmlNode art = xNode1.ChildNodes[1].Attributes.GetNamedItem("name");
            weather.WeatherType = art.Value;

            art = xNode1.ChildNodes[2].Attributes.GetNamedItem("value");
            string art1 = art.Value;

            art = xNode1.ChildNodes[5].Attributes.GetNamedItem("mps");
            art1 = art.Value;
            weather.WindSpeed = art1;

            art = xNode1.ChildNodes[4].Attributes.GetNamedItem("deg");
            art1 = art.Value;
            weather.WindDirection = art1;

            art = xNode1.ChildNodes[6].Attributes.GetNamedItem("value");
            weather.AirTemperature = Convert.ToInt32(art.Value);

            art = xNode1.ChildNodes[7].Attributes.GetNamedItem("value");
            art1 = art.Value;
            weather.Pressure = Convert.ToDouble(art1.Replace(".", ","), new CultureInfo("uk-UA")) * 0.75;
            weather.Date = DateTime.Now.ToShortDateString();
            weather.Humidity = "0";
            return weather;

        }
    }
}
