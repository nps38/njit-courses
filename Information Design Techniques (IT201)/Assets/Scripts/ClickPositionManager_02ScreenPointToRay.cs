using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickPositionManager_02ScreenPointToRay : MonoBehaviour
{
    public LayerMask clickMask;

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButtonDown(0) || Input.GetMouseButton(1))
        {
            //checking for user input
            Vector3 clickPosition = -Vector3.one;
            //method 2: raycast using colliders (use vector as direction)
            //cast ray from position of camera out through mouse to infinity
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); //don't need z distance
            //create raycasthit but it's automatically populated from where ray will hit collider
            RaycastHit hit; //don't have to addign, raycast will assign it procedurally
            /*
            if(Physics.Raycast(ray, out hit)) //export out info to hit
            //feed array, out means it will be updated
            //if there is collider (it hits something), true, else false
            {
                clickPosition = hit.point;
                GameObject.CreatePrimitive(PrimitiveType.Sphere);
                primitive.transform.position = clickPosition;
            }*/
            if(Physics.Raycast(ray, out hit, 100f, clickMask)) //float is max distance
            {
                //before array was going to infinity
                //shoot array to 100m and see if collision occurs
                //LayerMast - specifies layers
                //hit has a lot of info abt raycast collision on both sides
                clickPosition = hit.point;
                GameObject primitive = GameObject.CreatePrimitive(PrimitiveType.Sphere);
                primitive.transform.position = clickPosition;
                //but it hits everything which is a problem as the spheres populate more
                //so add physics layers and update Raycast method call
            }
            Debug.Log(clickPosition);
        }
    }
}
