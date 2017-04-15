using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace Server.Controllers
{
    [Route("api/[controller]")]
    public class HeartbeatController : Controller
    {
        // GET: api/values
        [HttpGet]
        public IActionResult Heartbeat()
        {
            return Ok("Kewl");
        }

        [HttpGet]
        [Route("init")]
        public IActionResult Initialize()
        {
            return Ok("That's oke");
        }
    }
}
