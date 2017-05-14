using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using ServiceLayer.DataAccess;
using ServiceLayer.DataAccess.Enums;

namespace ServiceLayer.Migrations
{
    [DbContext(typeof(HomeContext))]
    [Migration("20170514192254_SeparateTables")]
    partial class SeparateTables
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "1.1.1")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("ServiceLayer.DataAccess.Entities.Authentication", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<bool>("Success");

                    b.Property<DateTime>("Timestamp");

                    b.Property<int>("Type");

                    b.HasKey("Id");

                    b.ToTable("Authentication");
                });

            modelBuilder.Entity("ServiceLayer.DataAccess.Entities.Device", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<bool>("AlarmOn");

                    b.Property<string>("LastAddress");

                    b.Property<DateTime>("LastHeartbeat");

                    b.HasKey("Id");

                    b.ToTable("Devices");
                });

            modelBuilder.Entity("ServiceLayer.DataAccess.Entities.Door", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<int>("Status");

                    b.Property<DateTime>("Timestamp");

                    b.HasKey("Id");

                    b.ToTable("Door");
                });

            modelBuilder.Entity("ServiceLayer.DataAccess.Entities.Movement", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<DateTime>("Timestamp");

                    b.HasKey("Id");

                    b.ToTable("Movement");
                });

            modelBuilder.Entity("ServiceLayer.DataAccess.Entities.Weather", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<int>("Humidity");

                    b.Property<int>("Temperature");

                    b.Property<DateTime>("Timestamp");

                    b.HasKey("Id");

                    b.ToTable("Weather");
                });
        }
    }
}
