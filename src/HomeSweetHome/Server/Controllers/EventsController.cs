using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ServiceLayer.DataAccess;
using ServiceLayer.DataAccess.Entities;

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
        public async Task<IActionResult> Event(string eventType)
        {
            await context.Events.AddAsync(new Event
            {
                Address = HttpContext.Connection.RemoteIpAddress.ToString(),
                EventText = eventType,
                Time = DateTime.Now
            });

            await context.SaveChangesAsync();

            return Ok();
        }
    }
}
