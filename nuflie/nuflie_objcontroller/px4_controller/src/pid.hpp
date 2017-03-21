#pragma once

#include <ros/ros.h>
#include <fstream>
#include <iostream>

class PID
{
public:
    PID(
        float kp,
        float kd,
        float ki,
        float minOutput,
        float maxOutput,
        float integratorMin,
        float integratorMax,
        const std::string& name)
        : m_kp(kp)
        , m_kd(kd)
        , m_ki(ki)
        , m_minOutput(minOutput)
        , m_maxOutput(maxOutput)
        , m_integratorMin(integratorMin)
        , m_integratorMax(integratorMax)
        , m_integral(0)
        , m_previousError(0)
        , m_previousTime(ros::Time::now())
    {
    }

    void reset()
    {
        m_integral = 0;
        m_previousError = 0;
        m_previousTime = ros::Time::now();
    }

    void setIntegral(double integral)
    {
        m_integral = integral;
    }

    double ki() const//float
    {
        return m_ki;
    }

    double update(double value, double targetValue)//all float
    {
        ros::Time time = ros::Time::now();
        double dt = time.toSec() - m_previousTime.toSec();
        double error = targetValue - value;
        //ROS_INFO("error,%f,\n",error);
        if(fabs(error)> 6000)
          {
            error = 0;
          }  
  
        m_integral += error * dt;
        m_integral = std::max(std::min(m_integral, m_integratorMax), m_integratorMin);
        
        //ROS_INFO("m_integral,%f,\n",m_integral);
        double p = m_kp * error;
        double d = 0;
        if (dt > 0)
        {
            d = m_kd * (error - m_previousError) / dt;
        }
        double i = m_ki * m_integral;
        double output = p + d + i;
        m_previousError = error;
        m_previousTime = time;
        // self.pubOutput.publish(output)
        // self.pubError.publish(error)
        // self.pubP.publish(p)
        // self.pubD.publish(d)
        // self.pubI.publish(i)
        //ROS_INFO("output,%f,\n dt,%f",output,dt);
        return std::max(std::min(output, m_maxOutput), m_minOutput);

    }


private://float
    double m_kp;
    double m_kd;
    double m_ki;
    double m_minOutput;
    double m_maxOutput;
    double m_integratorMin;
    double m_integratorMax;
    double m_integral;
    //float m_integral1;
    //float m_integral2;
    double m_previousError;
    ros::Time m_previousTime;
};
