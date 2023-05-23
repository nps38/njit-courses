using System;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class Clock : MonoBehaviour
{
    public Transform hoursTransform, minutesTransform, secondsTransform;
    const float degreesPerHour = 30f, degreesPerMinute = 6f, degreesPerSecond = 6f, degreesPerDayCycle = 15f;
    private DateTime timeDiscrete;
    private TimeSpan timeContinuous;
    public bool continuous, realTime = true;
    public Transform dayCycle;
    //[Range(0, 24)]
    //public int hours;

    public Text textAMPM;
    private bool isAM;

    private float hours, minutes, hoursTemp;

    void Awake() {
        timeDiscrete = DateTime.Now;
        Debug.Log(DateTime.Now.TimeOfDay.Hours);
        //hours = (float)timeContinuous.TotalHours;
        minutes = (float)timeContinuous.TotalMinutes;
        hoursTransform.localRotation = Quaternion.Euler(0f, degreesPerHour * hours, 0f); 
        minutesTransform.localRotation = Quaternion.Euler(0f, degreesPerMinute * minutes, 0f);   
        secondsTransform.localRotation = Quaternion.Euler(0f, degreesPerSecond * timeDiscrete.Hour, 0f);
        dayCycle.localRotation = Quaternion.Euler(timeDiscrete.TimeOfDay.Hours * degreesPerDayCycle, 0f, 0f);
        //hours = timeDiscrete.TimeOfDay.Hours;

        if(hours<12)
        {
            isAM = true;
            textAMPM.text = "AM";
        }
        else
        {
            isAM = false;
            textAMPM.text = "PM";
        }
    }

    private void Update()
    {
        timeContinuous = DateTime.Now.TimeOfDay;
        hoursTransform.localRotation = Quaternion.Euler(0f, (float)timeContinuous.TotalHours * degreesPerHour, 0f);
        minutesTransform.localRotation = Quaternion.Euler(0f, (float)timeContinuous.TotalMinutes * degreesPerMinute, 0f);
        if (realTime)
        {
            hours = timeDiscrete.TimeOfDay.Hours;
            dayCycle.localRotation = Quaternion.Euler(timeDiscrete.TimeOfDay.Hours * degreesPerDayCycle, 0f, 0f);    
        }
        else
        {
            dayCycle.localRotation = Quaternion.Euler(hours * degreesPerDayCycle, 0f, 0f);
        }

        if(continuous)
        {
            UpdateContinuous();
        }
        else{
            UpdateDiscrete();
        }
    }
    void UpdateContinuous()
    {
        secondsTransform.localRotation = Quaternion.Euler(0f, (float)timeContinuous.TotalSeconds*degreesPerSecond, 0f);
    }
    void UpdateDiscrete()
    {
        timeDiscrete = DateTime.Now;
        secondsTransform.localRotation = Quaternion.Euler(0f, timeDiscrete.Second * degreesPerSecond, 0f);
    }
    public void UpdateTime(float clickedHourRotation)
    {
        hoursTemp = ((float)timeContinuous.TotalHours - (int)timeContinuous.TotalHours) + (clickedHourRotation/degreesPerHour);
        if (!isAM) hoursTemp += 12f;
        if((int)hoursTemp <(int) hours)
        {
            hours = hoursTemp;
            UpdateAMPM();
        }
        else hours = hoursTemp;
    }
    public void UpdateAMPM()
    {
        if(isAM)
        {
            isAM = false;
            textAMPM.text = "PM";
            hours += 12f;
        }
        else
        {
            isAM = true;
            textAMPM.text = "AM";
            hours -= 12f;
        }
    }
    public float getHours()
    {
        return hours;
    }
}
