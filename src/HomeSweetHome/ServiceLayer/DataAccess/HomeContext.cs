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

        public DbSet<Device> Devices { get; set; }
        public DbSet<Authentication> Authentication { get; set; }
        public DbSet<Door> Door { get; set; }
        public DbSet<Weather> Weather { get; set; }
        public DbSet<Movement> Movement { get; set; }

    }
}
