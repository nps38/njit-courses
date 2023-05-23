using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class ClickPositionManager_Sprint02 : MonoBehaviour
{
    private int shape = 0;
    private GameObject primitive;
    private float red = .8f, green = .8f, blue = .8f, destroyTime = 3f, timeToDestroy = 3f;
    public Text mousePosition, blueAmount, redAmount, greenAmount;
    //timerAmount

    [SerializeField]
    private float distance = 5f, distanceChange;

    private Vector3 clickPosition;
    private bool timedDestroyIsOn = true;
    private float size = 0.5f;

    private Vector3 lastClickPosition = Vector3.zero;
    //public Text lifeTime;

    public GameObject paintedObject00, paintedObject01, paintedObject02, explosion;
    private Color paintedObjectColor, paintedObjectEmission;

    public Clock clock;

    [SerializeField]
    [Range(0.1f, 1f)]
    private float emissionsStrength = 0.5f;
    private float opacityStrength = 0.5f;

    void Update ()
    { 
        if (Input.GetMouseButtonDown(0)) //left click
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); //similar to vector
            RaycastHit hit; //don't have to assign this, raycast will do it procedurally

            if (Physics.Raycast(ray, out hit)) //export out info to it (shoot out ray)
            {
                if(hit.transform.gameObject.layer == 11) //clockface
                {
                    hit.transform.parent.GetComponent<Clock>().UpdateTime(hit.transform.localEulerAngles.y);
                    //Debug.Log(hit.transform.rotation.ToString());
                }
            }
        }

        Debug.Log(EventSystem.current.currentSelectedGameObject == null);
        if (Input.GetMouseButton(0) && (EventSystem.current.currentSelectedGameObject == null)) //left hold
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); //similar to vector
            RaycastHit hit; //don't have to assign this, raycast will do it procedurally

            if (Physics.Raycast(ray, out hit)) //export out info to it (shoot out ray)
            {
                if(hit.transform.gameObject.layer == 12) //paintedObject
                {
                    Destroy(hit.transform.gameObject);
                    primitive = Instantiate(explosion, hit.transform.position, Quaternion.identity);
                    Destroy(primitive, 1f);
                }
            }
        }
        
        if(Input.GetMouseButtonUp(1)) //user release right mouse button so reset lastPosition to avoid large spawns
        {
            lastClickPosition = Vector3.zero;
        }

        if (Input.GetMouseButtonDown(1) || Input.GetMouseButton(1))
        {
            clickPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition + new Vector3(0f, 0f, distance));
            switch(shape)
            {
                case 0:
                    primitive = Instantiate(paintedObject00, clickPosition, Quaternion.identity);
                    //primitive = GameObject.CreatePrimitive(PrimitiveType.Sphere);
                    break;
                case 1:
                    primitive = Instantiate(paintedObject01, clickPosition, Quaternion.identity);
                    //primitive = GameObject.CreatePrimitive(PrimitiveType.Cube);
                    break;
                case 2:
                    primitive = Instantiate(paintedObject02, clickPosition, Quaternion.identity);
                    //primitive = GameObject.CreatePrimitive(PrimitiveType.Cylinder);
                    break;
                default:
                    break;
            }
            //primitive.transform.localScale = new Vector3(Random.Range(0.1f, 1f)*size,Random.Range(0.1f, 1f)*size,Random.Range(0.1f, 1f)*size);
            if (lastClickPosition == Vector3.zero)
            {
                primitive.transform.localScale = new Vector3(Random.Range(0.1f, 1f)*size,Random.Range(0.1f, 1f)*size,Random.Range(0.1f, 1f)*size);
            }
            else
            {
                float x = Mathf.Clamp(Random.Range(size, size*6f) * Mathf.Abs(lastClickPosition.x - clickPosition.x), .1f, size*5f);
                float y = Mathf.Clamp(Random.Range(size, size*6f) * Mathf.Abs(lastClickPosition.y - clickPosition.y), .1f, size*5f);
                float z = (x+y)/2f;
                primitive.transform.localScale = new Vector3(x,y,z);
            }
            
            //randomizing colors and scale
            //primitive.transform.position = clickPosition;
            paintedObjectColor = new Color(Random.Range(0.0f, red), Random.Range(0.0f, green), Random.Range(0.0f, blue), opacityStrength);
            primitive.GetComponent<Renderer>().material.color = paintedObjectColor;
            paintedObjectEmission = new Color(paintedObjectColor.r * emissionsStrength, paintedObjectColor.g * emissionsStrength, paintedObjectColor.b * emissionsStrength);
            primitive.GetComponent<Renderer>().material.SetColor("_EmissionColor", paintedObjectEmission);
            
            primitive.transform.parent = this.transform;
            if(timedDestroyIsOn)
            {
                Destroy(primitive, timeToDestroy);
            }
            lastClickPosition = clickPosition;
        }
        mousePosition.text = "Mouse Position x: " + Input.mousePosition.x.ToString("F0") + ", y: " + Input.mousePosition.y.ToString("F0");
    }

    public void changeShape(int tempShape)
    { shape = tempShape;}

    public void changeRed(float tempRed)
    { 
        red = tempRed;
        redAmount.text = (red * 100f).ToString("F0");
    }

    public void changeGreen(float tempGreen)
    { 
        green = tempGreen;
        greenAmount.text = (green * 100f).ToString("F0");
    }

    public void changeBlue(float tempBlue)
    { 
        blue = tempBlue;
        blueAmount.text = (blue * 100f).ToString("F0");
    }

    public void destroyObjects()
    {
        foreach (Transform child in transform)
        {
            Destroy(child.gameObject);
            primitive = Instantiate(explosion, child.position, Quaternion.identity);
            Destroy(primitive, 1f);
        }
    }

    public void ToggleTimeDestroy(bool timer)
    {
        timedDestroyIsOn = timer;
    }

    public void changeTimeToDestroy(float temp)
    {
        timeToDestroy = temp;
        //timerAmount.text = timeToDestroy.ToString("F0") + "sec";
    }
    public void changeSize(float temp)
    {
        foreach (Transform child in transform)
        {
            child.localScale = child.localScale*temp/size;
        }
        size = temp;
    }
    public void changeEmissionStrength(float temp)
    {
        foreach(Transform child in transform)
        {
            paintedObjectColor = child.GetComponent<Renderer>().material.GetColor("_Color");
            paintedObjectEmission = new Color(paintedObjectColor.r * temp, paintedObjectColor.g*temp, paintedObjectColor.b*temp);
            child.GetComponent<Renderer>().material.SetColor("_EmissionColor", paintedObjectEmission);
        }
        emissionsStrength = temp;
    }
    public void changeOpacityStrength(float temp)
    {
        foreach(Transform child in transform)
        {
            paintedObjectColor = child.GetComponent<Renderer>().material.GetColor("_Color");
            paintedObjectColor.a = temp;
            child.GetComponent<Renderer>().material.SetColor("_Color", paintedObjectColor);
        }
        opacityStrength = temp;
    }
}