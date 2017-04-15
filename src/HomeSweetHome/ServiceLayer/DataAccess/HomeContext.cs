using Microsoft.EntityFrameworkCore;
using ServiceLayer.DataAccess.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess
{
    public class HomeContext : DbContext
    {
        public HomeContext(DbContextOptions<HomeContext> options) : base(options)
        {   }

        public DbSet<Heartbeat> Heartbeats { get; set; }
        public DbSet<Event> Events { get; set; }
    }
}
