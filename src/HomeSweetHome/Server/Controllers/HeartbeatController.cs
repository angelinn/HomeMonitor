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
    public class HeartbeatController : Controller
    {
        private readonly HomeContext context;
        public HeartbeatController(HomeContext context)
        {
            this.context = context;
        }

        // GET: api/values
        [HttpGet]
        public async Task<IActionResult> Heartbeat()
        {
            string address = HttpContext.Connection.RemoteIpAddress.ToString();

            await context.Heartbeats.AddAsync(new Heartbeat { Address = address, Time = DateTime.Now });
            await context.SaveChangesAsync();
            return Ok();
        }

        [HttpGet]
        [Route("init")]
        public IActionResult Initialize()
        {
            return Ok("That's oke");
        }
    }
}
