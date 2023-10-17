# IGC_UE
This document is currently a work in progress.
 
Plugin build for Unreal Engine 4.27. This plugin will capture renders spun around a target object and export out a JSON file of the relative camera transforms. It will upload the necessary files to the IGC API to process to re-create a printable mesh.

## How to use
### Step 1: Set Up
* Get your API Key from the [IGC Platform](https://platform.igc.studio/collectables)
* Attach *BP_Capturer* to target Actor
* Input your API_key into *BP_Capturer*
* Adjust *Radius* to fit whole Actor
* Read the [Best Practices](https://github.com/In-Game-Collectables/IGC_UE4#best-practices) section for the ideal set up
### Step 2: Capturing:
* Use event *Capture* in *BP_Capturer*. This will export out all needed renders/files
    * The input parameter *Async* determines if there should be a delay between captures
        * If *Async* is false, this may freeze the game up to a couple seconds depending on the dimensions of the renders
        * *Async* should NOT be used if the Target character or lighting can animate/change between frames
* Renders/files will be outputed to *PROJECTNAME/OUTPUTS/Captures/*
* The event *CaptureAndUpload* can be used to combine the steps for Capturing and Uploading
### Step 3: Uploading
* Use event *Upload Captures* in *BP_Capturer*. This will upload all images and files within *PROJECTNAME/OUTPUTS/Captures/* to the API
* The event dispatcher *onUploadFinished* will be called when the Upload finishes. It will return:
    * Succeeded: Whether the upload succeeded
    * Message: Information about if the upload succeeded or why it failed
    * QRTexture: QR Code Texture of the link to the Checkout page
    * Checkout URL to the Checkout page
### Step 4: Checkout
* Use the event dispatcher *onUploadFinished* to get either the link to the Checkout page or the Texture2D of the QR Code

<br />

### Parameters

Capturing:
* API_Key
    * API Key for the IGC Platform
* Frame Count
    * Number of images to be rendered out
* Radius
    * Radius around the target actor the camera will go
* Camera FOV
    * Field of View of render camera
* Render Size
    * Dimensions of render width & height
* Extra Actors
    * Any extra actors that should be rendered out with the Actor

Rendering:
* Brightness
    * Brightness multiplier for render outputs
* Contrast
    * To adjust contrast for render outputs
* Desaturation
    * To lower colour saturation of render outputs

## Notes
* The Capturer will render out attached Actor, the Actor's children and and *Extra Actors*
* The variable *CurrentStage* on *BP_Capturer* can be used to see if it is currently Capturing, Uploading, CheckingOut, or not doing anything.
* Warning: If *Auto-Exposure* is turned on within the project, the render will not match what the viewport looks like. It will probably instead seem much dimmer.
    * Use the *Render Parameters* on *BP_Capturer* to boost the brightness in this case.

## Best Practices
### Settings
* At least 100 frames at 1024x1024 should be uploaded for best quality.
### Mesh
* The character should take up as much space possible within the renders without cutting anything off.
* The mesh should not have any floating pieces.
* Backfaces should not be missing.
### Rendered Image
* Use the *Render Parameters* wihtin *BP_Capturer* to make adjustments to the final render if you would like them brighter etc.
### Lighting & Materials
* Having an evenly lit character will give the best results. Any shadows/lighting on the mesh will be baked into the final model.
* Pure unlit shaders are not recommended. The meshing process needs at least a bit of shading to figure out the depth of points within a model.
* Recommended lighting set ups:
    * Lit shaders with ambient lighting
    * Lit shaders with fixed lights around character
    * Unlit shaders with strong ambient occlusion
* Materials with high roughness and little specular are recommended.
    * Highly specular and highly metallic materials will create artifacts within the final model.
* Lighting is even more important on simple, stylized characters, as any shadows baked on are a lot more noticeable.

<p align="center">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/7e9cc2ff-6b6d-4bad-ad04-623516f5c90f" width="512" height="256">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/c0c76996-15bb-43bb-b677-d2165eb56a15" width="512" height="256">
 <p align="center">Directional Lighting vs. Evenly Shaded</p>
</p>

### Ideal Lighting Examples
<p align="center">

![pigeon](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/13398085-397f-43d2-8756-01e94a8c5d3d)

![robot](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/51be5bf6-64f0-45fa-85ec-996c11f8b183)

![mushroom](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/1604f6ef-7124-40d0-9a0d-7403ae29ded6)

</p>

[Pigeon](https://sketchfab.com/3d-models/pigeon-quirky-series-e607ed34d37d433496d5a557c8230b28)

[Robot](https://sketchfab.com/3d-models/robot-4-b0c5f2f5ac04402dad029d6516d706b9)

[Mushroom](https://sketchfab.com/3d-models/cuute-mushroom-ffc370ddc6d542d590b9f503d0892ce0)
