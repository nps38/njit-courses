using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickPositionManager_00randomScaleColor : MonoBehaviour
{
    private GameObject primitive;
    void Update()
    {
        if(Input.GetMouseButtonDown(0) || Input.GetMouseButton(1))
        {
            Vector3 clickPosition = -Vector3.one;

            Plane plane = new Plane(Vector3.forward, 0f);
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            float distanceToPlane;

            if(plane.Raycast(ray, out distanceToPlane))
            {
                clickPosition = ray.GetPoint(distanceToPlane);
            }

            Debug.Log(clickPosition);
            primitive = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            //randomizing colors and scale
            primitive.transform.localScale = new Vector3(Random.Range(0.1f, 1f), Random.Range(0.1f, 1f), Random.Range(0.1f, 1f));
            primitive.transform.position = clickPosition;
            primitive.GetComponent<Renderer>().material.color = new Vector4(Random.Range(0f, 1f),Random.Range(0f, 1f),Random.Range(0f, 1f),1f);
            Destroy(primitive, 3f);
        }
    }
}
