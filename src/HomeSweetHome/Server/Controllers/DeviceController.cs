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
    public class DeviceController : Controller
    {
        private readonly HomeContext context;
        public DeviceController(HomeContext context)
        {
            this.context = context;
        }

        // GET: api/values
        [HttpGet]
        [Route("Heartbeat")]
        public async Task<IActionResult> Heartbeat(int id)
        {
            Device current = context.Devices.FirstOrDefault(d => d.DeviceId == id);
            bool newDevice = current == null;
            if (newDevice)
                current = new Device { DeviceId = id };

            current.LastAddress = HttpContext.Connection.RemoteIpAddress.ToString();
            current.LastHeartbeat = DateTime.Now;

            if (newDevice)
                await context.Devices.AddAsync(current);
            else
                context.Devices.Update(current);

            await context.SaveChangesAsync();

            return Ok();
        }

        [HttpGet]
        [Route("IsOnline")]
        public async Task<IActionResult> IsOnline(int id)
        {
            Device current = await context.Devices.FindAsync(id);
            if (current == null)
                return BadRequest("Device not found.");

            string status = (DateTime.Now - current.LastHeartbeat < TimeSpan.FromSeconds(35)) ? "online" : "offline";
            return Ok($"{{status: \"{status}\"}}");
        }
    }
}
