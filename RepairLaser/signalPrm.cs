using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using INIFile;

namespace SignalGenerator
{
    class signalPrm
    {
        public int portNumber;
        public int baudRate;
        public int recvTime;
        public string modelName;
        public string patterName;

        private string prmFile = "./RepairPrm.ini";
        private string signalSection = "SignalPrm";

        public bool savePrm()
        {
            bool ret = true;
            ret = ret && INIOperationClass.writeKey(prmFile, signalSection, "portNumber", portNumber);
            ret = ret && INIOperationClass.writeKey(prmFile, signalSection, "baudRate", baudRate);
            ret = ret && INIOperationClass.writeKey(prmFile, signalSection, "recvTime", recvTime);
            ret = ret && INIOperationClass.writeKey(prmFile, signalSection, "modelName", modelName);
            ret = ret && INIOperationClass.writeKey(prmFile, signalSection, "patterName", patterName);

            return ret;
        }

        public bool initPrm()
        {
            bool ret = true;

            ret = ret && INIOperationClass.readKey(prmFile, signalSection, "portNumber", ref portNumber);
            ret = ret && INIOperationClass.readKey(prmFile, signalSection, "baudRate", ref baudRate);
            ret = ret && INIOperationClass.readKey(prmFile, signalSection, "recvTime", ref recvTime);
            ret = ret && INIOperationClass.readKey(prmFile, signalSection, "modelName", ref modelName);
            ret = ret && INIOperationClass.readKey(prmFile, signalSection, "patterName", ref patterName);
            return ret;
        }
    }
}
