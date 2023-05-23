using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickPositionManager_03PlaneRaycast : MonoBehaviour
{
    //don't need the layer mask and switched variable declaration to global
    private GameObject primitive;

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButtonDown(0) || Input.GetMouseButton(1))
        {
            //goal: log click position in world space to console

            //create vector to store mouse position
            //set it to a default value whose value will neber be recorded from mouse position
            //so when start clicking will get results of (-1,-1,-1) that we know if not real info

            Vector3 clickPosition = -Vector3.one;

            //method 3: raycast using plane
            Plane plane = new Plane(Vector3.forward, 0f);
            //float is where it's being position - how high up it is
            //Plane plane = new Plane(Vector3.forward, 0f);
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            //shoot out ray
            float distanceToPlane;

            if(plane.Raycast(ray, out distanceToPlane))
            {
                clickPosition = ray.GetPoint(distanceToPlane);
            }

            //print out the position and spawn a sphere

            Debug.Log(clickPosition);
            primitive = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            primitive.transform.position = clickPosition;
        }
    }
}
