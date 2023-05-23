using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickPositionManager_01ScreenToWorldPoint : MonoBehaviour
{
    [Range(1f, 30f)]
    [SerializeField]
    public float distance = 3f;
    public GameObject fancy;
    [Range(-3f, 3f)]
    [SerializeField]
    public float distanceChange = 1f;

    private void Update()
    {
        if (Input.GetMouseButtonDown(0) || Input.GetMouseButton(1))
        {
            distance += distanceChange;

            //goal: log click position in world space to the console
            //create a vector to store the mouse position
            //set it to default value whose value will never be recorded from the mouse position
            //so when start clicking will get results of (-1,-1,-1) that we know if not real info

            Vector3 clickPosition = -Vector3.one;

            //method 1: ScreenToWorldPoint
            //going to use it, a built-in unity method that derives fromcameras
            //vector to pass method contains two main pieces of info
            //x and y coordinates are the pixel locations on the screen where the mouse is
            //can get that from Input.mousePosition but z is zero from that
            //we need a z location of how far into the virtual world that we want to determine our click was at
            //for now, we have arbitrary pick z=5
            clickPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition + new Vector3(0f, 0f, distance));

            //print out the position and spawn a sphere
            Debug.Log(clickPosition);
            //GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            //sphere.transform.position = clickPosition;

            GameObject tempGO = Instantiate(fancy, clickPosition, Quaternion.identity);
            //Instantiate(fancy);
            //fancy.transform.position = clickPosition;
            Destroy(tempGO, 3f);
        }
    }

    public void ChangeDistance(float change)
    {
        distance = change;
    }

    public void ChangeDistanceDelta(float change)
    {
        distanceChange = change;
    }
}
