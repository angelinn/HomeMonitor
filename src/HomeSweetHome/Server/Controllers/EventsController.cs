using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ServiceLayer.DataAccess;
using ServiceLayer.DataAccess.Entities;
using ServiceLayer.DataAccess.Enums;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace Server.Controllers
{
    [Route("api/[controller]")]
    public class EventsController : Controller
    {
        private readonly HomeContext context;

        public EventsController(HomeContext context)
        {
            this.context = context;
        }

        [HttpGet]
        [Route("Weather")]
        public async Task<IActionResult> Weather(string temperature, string humidity)
        {
            await context.Weather.AddAsync(new Weather
            {
                Temperature = Int32.Parse(temperature),
                Humidity = Int32.Parse(humidity),
                Timestamp = DateTime.Now
            });

            await context.SaveChangesAsync();

            return Ok();
        }

        [HttpGet] 
        [Route("Door")]
        public async Task<IActionResult> Door(int status)
        {
            await context.Door.AddAsync(new Door
            {
                Status = (DoorStatus)status,
                Timestamp = DateTime.Now
            });

            await context.SaveChangesAsync();
            return Ok();
        }

        [HttpGet]
        [Route("Movement")]
        public async Task<IActionResult> Movement()
        {
            await context.Movement.AddAsync(new Movement
            {
                Timestamp = DateTime.Now
            });

            await context.SaveChangesAsync();
            return Ok();
        }
    }
}
