using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using ServiceLayer.DataAccess;

namespace ServiceLayer.Migrations
{
    [DbContext(typeof(HomeContext))]
    [Migration("20170415203049_InitialCreate")]
    partial class InitialCreate
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "1.1.1")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("ServiceLayer.DataAccess.Entities.Event", b =>
                {
                    b.Property<int>("EventId")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("Address");

                    b.Property<string>("EventText");

                    b.Property<DateTime>("Time");

                    b.HasKey("EventId");

                    b.ToTable("Events");
                });

            modelBuilder.Entity("ServiceLayer.DataAccess.Entities.Heartbeat", b =>
                {
                    b.Property<int>("HeartbeatId")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("Address");

                    b.Property<DateTime>("Time");

                    b.HasKey("HeartbeatId");

                    b.ToTable("Heartbeats");
                });
        }
    }
}
