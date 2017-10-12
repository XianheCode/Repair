using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace dataPro
{
    class Program
    {
        static void Main(string[] args)
        {
             int NUM = 696;
            StreamReader sr = new StreamReader("pos.txt");

            double[] pos_x = new double[NUM];
            double[] pos_y = new double[NUM];

            for(int i = 0; i<NUM; i++)
            {
                double.TryParse(sr.ReadLine(), out pos_x[i]);
                double.TryParse(sr.ReadLine(), out pos_y[i]);
            }

            double[] path_x, path_y;
            int path_number;

            datapro(pos_x, pos_y, NUM, 0.001, out path_x, out path_y, out path_number);

            for (int i = 0; i < path_number; i++ )
            {
                Console.WriteLine("{0}:({1},{2})", i, path_x[i], path_y[i]);
            }


                Console.ReadKey();

        }

        static void datapro(double[] pos_x, double[] pos_y,  int pos_number,
            double gap, out double[] path_x, out double[] path_y, out int path_number)
        {
            path_x = null;
            path_y = null;
            path_number = 0;
            if (pos_x.Length != pos_number || pos_y.Length != pos_number)
                return;
            path_x = new double[pos_number];
            path_y = new double[pos_number];

            path_x[0] = pos_x[0];
            path_y[0] = pos_y[0];

            int k = 0;
            double temp_x = path_x[k];
            double temp_y = path_y[k];
            k++;
            

            for(int i=1;i<pos_number;i++)
            {
                while( i < pos_number && distance(pos_x[i], pos_y[i], temp_x, temp_y) < gap)
                {
                    i++;
                }

                if(i < pos_number)
                {
                    
                    temp_x = path_x[k] = pos_x[i];
                    temp_y = path_y[k] = pos_y[i];
                    k++;
                    
                }
                else
                {
                    if(distance(pos_x[0], pos_y[0], temp_x, temp_y) >= gap)
                    {
                        temp_x = path_x[k] = pos_x[i];
                        temp_y = path_y[k] = pos_y[i];
                        k++;
                    }
                }
            }

            path_number = k;
        }

        static double distance(double x1, double y1, double x2, double y2)
        {
            double temp = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
            temp = Math.Sqrt(temp);
            return temp;
        }

    }
}
