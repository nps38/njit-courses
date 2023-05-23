using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UnitClick : MonoBehaviour
{
    // Start is called before the first frame update (initialization)
    /*private void Start()
    {
        Debug.Log("this is the unity console");
    }

    // Update is called once per frame
    private void Update()
    {
        Debug.Log("this is the update method");
    }*/

    public void OnMouseDown()
    {
        Debug.Log(name + " was clicked, only world position returned is " + transform.position); 
    }
}
