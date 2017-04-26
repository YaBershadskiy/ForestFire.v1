using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using ForestFires.DAL.Context;
using ForestFires.Models;
using ForestFires.Services;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace ForestFires.DataRecieve
{
    public class Test
    {
        public int ID { get; set; }
        public int Temperature { get; set; }
        public int Humidity { get; set; }
        public int Smoke { get; set; }
    }
    public class DataReciever
    {
        public delegate void GetDataDelegate();

        public GetDataDelegate myDelegate;

        private readonly int _baud_rate = 57600;
        private readonly string _port = "COM1";
        private readonly DBWorker _dbw;
        private readonly SensorsContext _context;
        public Test ReadData { get; set; }
        public SerialPort _dataPort = new SerialPort();

        public DataReciever(SensorsContext context)
        {
            myDelegate = new GetDataDelegate(RecieveData);
            _context = context;
            _dbw = new DBWorker(_context);
        }

        public void RecieveData()
        {
            if (!_dataPort.IsOpen)
            {
                _dataPort.PortName = _port;
                _dataPort.BaudRate = _baud_rate;
                _dataPort.DataBits = 8;
                _dataPort.Parity = Parity.None;
                _dataPort.StopBits = StopBits.One;
                _dataPort.DtrEnable = true;
                _dataPort.RtsEnable = false;
                _dataPort.ReadTimeout = (1000);
                _dataPort.WriteTimeout = (1000);
                _dataPort.DataReceived += new SerialDataReceivedEventHandler(DataRecieveHandler);
                try
                {
                    _dataPort.Open();
                }
                catch (Exception ex)
                {

                }
            }
        }

        public void DataRecieveHandler(object sender, SerialDataReceivedEventArgs e)
        {
            // \n\r
            SerialPort sp = _dataPort;
            for (int i = 0; i < 10000; i++)
            {
                for(int j =0;j<1000;j++)
                { }
            }
            String _input = sp.ReadExisting();
            
            UseData(_input);
        }

        public void UseData(string _input)
        {
            String[] separators = new string[] { "\n\r" };
            String input = _input.Split(separators, StringSplitOptions.RemoveEmptyEntries).LastOrDefault();
            Test data = new Test();
            if (input != null)
            {
                if (input.Length > 0)
                {
                    MatchCollection mc = Regex.Matches(input, "(\\n\\r)?(?<Prop>\\w*):(?<Value>\\d*)(\\,\\s)?");
                    Int32 tempData = 0;
                    Int32.TryParse(mc[0].Groups["Value"].Value, out tempData);
                    if (tempData != 0) data.ID = tempData;
                    tempData = 0;
                    Int32.TryParse(mc[1].Groups["Value"].Value, out tempData);
                    if (tempData != 0) data.Temperature = tempData;
                    tempData = 0;

                    Int32.TryParse(mc[2].Groups["Value"].Value, out tempData);
                    if (tempData != 0) data.Smoke = tempData;

                    tempData = 0;

                    Int32.TryParse(mc[3].Groups["Value"].Value, out tempData);
                    if (tempData != 0) data.Humidity = tempData;
                    //SMoke > 1000 || Temperature >40 Status = Fire
                    Status status = Status.Ok;
                    if (data.Temperature >= 45 || data.Smoke >= 1200) status = Status.Fire;
                    using (
                        var dbWorker =
                            new DBWorker(
                                new SensorsContext(
                                    "Server=(LocalDB)\\MSSQLLocalDB;Database=SensorsDBv1;Trusted_Connection=True;MultipleActiveResultSets=true"))
                    )
                    {
                        bool temp = false;
                        try
                        {
                            temp = dbWorker.UpdateData(data.ID, Convert.ToDouble(data.Temperature),
                                Convert.ToDouble(data.Humidity), Convert.ToDouble(data.Smoke), DateTime.Now, status,
                                new SensorsContext(
                                    "Server=(LocalDB)\\MSSQLLocalDB;Database=SensorsDBv1;Trusted_Connection=True;MultipleActiveResultSets=true"));
                        }
                        catch (Exception exception)
                        {
                            temp = true;
                        }

                        ReadData = data;
                        int c = 0;
                        while (!temp)
                        {
                            c++;
                        }
                    }
                }
            }
        }


    }
}
