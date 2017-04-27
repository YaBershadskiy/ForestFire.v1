using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using ForestFires.DataRecieve;
using ForestFires.DAL.Context;
using Microsoft.AspNetCore.Mvc;
using ForestFires.Models;
using ForestFires.Services;

namespace ForestFires.Controllers
{
    public class HomeController : Controller
    {
        private readonly SensorsContext _context;
        private DBWorker dbw;
        private DataReciever dr;

        public HomeController(SensorsContext context)
        {
            _context = context;
            dbw = new DBWorker(_context);
            dr = new DataReciever(_context);
        }

        [HttpPost]
        public JsonResult AjaxWeatherResponse()
        {
            WeatherData wd = Weather.GetWeatherFromSiteToday();
            return Json("[\"" + wd.Date.ToString() + "\",\"" + wd.AirTemperature.ToString() + "°C\", \"" + wd.Humidity.ToString() + "%\", \"" + wd.WindSpeed + " m/s\"," + wd.WindDirection +"]");
        }

        [HttpPost]
        public JsonResult AjaxSensorsResponse()
        {
            var a = dbw.GetSensors().Where(Sensor => Sensor.Id == 1).FirstOrDefault();
            return Json(a);
        }

        public IActionResult Index()
        {
            List<Sensor> locations = new List<Sensor>();
            //Update sensor data
            //dbw.UpdateData(id, temperature, humidity, smoke);

            //Create new sensor
            //dbw.SetDataFromObject(new Sensor(50.008189, 36.242334, 17.5, 15, 30,DateTime.Now, Status.Ok));
            //dbw.SetDataFromObject(new Sensor(50.048189, 36.252334, 45, 18, 22,DateTime.Now, Status.Ok));
            //dbw.SetDataFromObject(new Sensor(50.028189, 36.242834, 42, 12, 32, DateTime.Now, Status.Fire));
            //or
            //dbw.SetDataFromParams(latt,lngt,temperature,humidity,smoke)
            List<WeatherData> WDL = new List<WeatherData>();
            try
            {
                WeatherData wd = Weather.GetWeatherFromSiteToday();
                WDL.Add(wd);
                ViewBag.Weather = WDL;
            }
            catch (Exception ex)
            {
            }

            locations = dbw.GetSensors().ToList();
            return View(locations);
        }

        public JsonResult StartThread()
        {
            try
            {
                Thread daThread = new Thread(dr.RecieveData);
                daThread.Start();
            }
            catch (Exception ex)
            {
                try
                {
                    Thread daThread = new Thread(dr.RecieveData);
                    daThread.Start();
                }
                catch (Exception)
                {

                }
            }
            return new JsonResult("");
        }

        public IActionResult Error()
        {
            return View();
        }
    }
}