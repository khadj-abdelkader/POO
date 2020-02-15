using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace Hercules
{
    public partial class Form1 : Form
    {
        public bool _continue { get; private set; }
        public object readThread { get; private set; }
        char Write;
        string Data;
        public string[] listeCaracteres = new string[] { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US" };

        public Form1()
        {
            InitializeComponent();
           
        }
       
        public void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
         
        }


        public void BaudRate()
        {


            // serialPort1.PortName = SetPortName(serialPort1.PortName);
            serialPort1.BaudRate = int.Parse(comboBox2.SelectedItem.ToString());
        


        }

        private int SetPortBaudRate(int baudRate)
        {
            throw new NotImplementedException();
        }

        private string SetPortName(string portName)
        {
            throw new NotImplementedException();
        }

        private void Open_Click(object sender, EventArgs e)
        {
            try
            {

           
             serialPort1.PortName = comboBox2.SelectedItem.ToString();
            BaudRate();
            serialPort1.Open();
            }
            catch (Exception) { }

            textBox2.Text = textBox2.Text + "\r\n" + "Serial port" + " " + comboBox1.Text + " " + "opened";
        }

        private void Close_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
            
            
        }

        public void RefreshSerialPort()
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox1.Items.Clear();

            if (ports.Length == 0)
            {
                comboBox1.Items.Add("Aucun port disponible");
            }
            else
            {
                comboBox1.BeginUpdate();
                foreach (string port in ports)
                {
                    comboBox1.Items.Add(port);
                }
                comboBox1.EndUpdate();
            }
        }



        delegate void SetTextCallback(int text);
        private void SetText(int text)
        {
            if (textBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                textBox1.Invoke(d, new object[] { text });
            }
            else
                textBox1.Text += Convert.ToChar(text);

        }

        private void Close_Click_1(object sender, EventArgs e)
        {
            textBox2.Text = textBox2.Text + "\r\n" + "Serial port" + " " + comboBox1.Text + " " + "closed";
        }

        

        private void Form1_Load(object sender, EventArgs e)
        {
            RefreshSerialPort();
            try
            {
                serialPort1.BaudRate = int.Parse(comboBox2.SelectedItem.ToString());
                serialPort1.Parity = Parity.None;
                serialPort1.StopBits = StopBits.One;
                serialPort1.DataBits = 8;
            }

            catch (Exception) { }
            }

        private void Send_Click_1(object sender, EventArgs e)
        {
           string Data = textBox1.Text;
            serialPort1.WriteLine(Data);
        }

    }
}
