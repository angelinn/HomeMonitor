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
        public async Task<IActionResult> Update(int id)
        {
            Device current = await context.Devices.FindAsync(id);
            bool newDevice = current == null;
            if (newDevice)
                current = new Device();

            current.LastAddress = HttpContext.Connection.RemoteIpAddress.ToString();
            current.LastHeartbeat = DateTime.Now;

            //if (!current.IsOnline)
            //    current.IsOnline = true;

            if (newDevice)
                await context.Devices.AddAsync(current);
            else
                context.Devices.Update(current);

            await context.SaveChangesAsync();

            return Ok();
        }

        [HttpGet]
        public async Task<IActionResult> IsOnline(int id)
        {
            Device current = await context.Devices.FindAsync(id);
            if (current == null)
                return BadRequest("Device not found.");

            //if (!current.IsOnline)
            //    return Ok("{status: \"offline\"");

            //if (current.IsOnline && (DateTime.Now - current.LastHeartbeat) < TimeSpan.FromSeconds(35))
            //{
            //    current.IsOnline = false;
            //    context.Update(current);
            //    await context.SaveChangesAsync();

            //    return Ok("{status: \"offline\"");
            //}

            return Ok("{status: \"online\"");
        }
    }
}
