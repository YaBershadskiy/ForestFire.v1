using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ForestFires.DAL.Context;
using Microsoft.AspNetCore.Mvc;
using ForestFires.Models;
using ForestFires.Services;

namespace ForestFires.Controllers
{
    public class HomeController : Controller
    {
        private readonly SensorsContext _context;
        private readonly DBWorker dbw;

        public HomeController(SensorsContext context)
        {
            _context = context;
            dbw = new DBWorker(_context);
        }
        public IActionResult Index()
        {
            List<Sensor> locations = new List<Sensor>();
            //Update sensor data
            //dbw.UpdateData(id, temperature, humidity, smoke);

            //Create new sensor
            //dbw.SetDataFromObject(new Sensor(50.008189, 36.242334, 17.5, 15, 30, DateTime.Now, Status.Ok));
            //dbw.SetDataFromObject(new Sensor(50.048189, 36.252334, 45, 18, 22, DateTime.Now, Status.Ok));
            //dbw.SetDataFromObject(new Sensor(50.028189, 36.242834, 42, 12, 32, DateTime.Now, Status.Fire));
            //or
            //dbw.SetDataFromParams(latt,lngt,temperature,humidity,smoke);

            locations = dbw.GetSensors().ToList();
            return View(locations);
        }

        public IActionResult Error()
        {
            return View();
        }
    }
}
