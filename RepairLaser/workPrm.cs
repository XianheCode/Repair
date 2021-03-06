﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using INIFile;

namespace RepairLaser
{
    class workPrm
    {
        public double startPos_x = 0;
        public double startPos_y = 0;
        public double PhotoPos_x = 0;
        public double PhotoPos_y = 0;
        public double endPos_x = 0;
        public double endPos_y = 0;
        public double FocusPos_z = 0;
        public double FocusPos_z_2 = 0;

        public double[] pos_x = new double[9];
        public double[] pos_y = new double[9];

        public double gap = 0.001;

        private string prmFile = "./RepairPrm.ini";
        private string LaserSection = "LaserPrm";
        private string PosSection = "PosPrm";
        private string WorkSection = "WorkPrm";



        public bool savePrm()
        {
            bool ret = true;
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "startPos_x", startPos_x);
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "startPos_y", startPos_y);
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "PhotoPos_x", PhotoPos_x);
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "PhotoPos_y", PhotoPos_y);
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "endPos_x", endPos_x);
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "endPos_y", endPos_y);
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "FocusPos_z", FocusPos_z);
            ret = ret && INIOperationClass.writeKey(prmFile, PosSection, "FocusPos_z_2", FocusPos_z_2);
            
            ret = ret && INIOperationClass.writeKey(prmFile, WorkSection, "gap", gap);

            for (int i = 0; i < 9; i++ )
            {
                string namex = "Pos_" + i.ToString() + "_x";
                string namey = "Pos_" + i.ToString() + "_y";
                ret = ret && INIOperationClass.writeKey(prmFile, PosSection, namex, pos_x[i]);
                ret = ret && INIOperationClass.writeKey(prmFile, PosSection, namey, pos_y[i]);
            }

            return ret;
        }

        public bool initPrm()
        {
            return readPrm();
        }


        public bool readPrm()
        {
            bool ret = true;

            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "startPos_x", ref startPos_x);
            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "startPos_y", ref startPos_y);
            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "PhotoPos_x", ref PhotoPos_x);
            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "PhotoPos_y", ref PhotoPos_y);
            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "endPos_x", ref endPos_x);
            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "endPos_y", ref endPos_y);
            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "FocusPos_z", ref FocusPos_z);
            ret = ret && INIOperationClass.readKey(prmFile, PosSection, "FocusPos_z_2", ref FocusPos_z_2);

            ret = ret && INIOperationClass.readKey(prmFile, WorkSection, "gap", ref gap);

            for (int i = 0; i < 9; i++)
            {
                string namex = "Pos_" + i.ToString() + "_x";
                string namey = "Pos_" + i.ToString() + "_y";
                ret = ret && INIOperationClass.readKey(prmFile, PosSection, namex, ref pos_x[i]);
                ret = ret && INIOperationClass.readKey(prmFile, PosSection, namey, ref pos_y[i]);
            }

            return ret;
        }
    }
}
