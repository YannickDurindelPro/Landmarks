import cv2
import mediapipe as mp

# Load the FaceMesh module
mp_face_mesh = mp.solutions.face_mesh

# Initialize the FaceMesh instance
face_mesh = mp_face_mesh.FaceMesh(
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

# Load an image using OpenCV
image_path = '/home/eyelights/Documents/landmarks/frame.jpg'
image = cv2.imread(image_path)

# Convert the image to RGB format (required by MediaPipe)
image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# Process the image and get the result
results = face_mesh.process(image_rgb)
file1 = open("landmarks_coordinates.txt","w")

# Check if any faces were detected
if results.multi_face_landmarks:
    for face_landmarks in results.multi_face_landmarks:
        for landmark in face_landmarks.landmark:
            x = int(landmark.x * image.shape[1])
            y = int(landmark.y * image.shape[0])
            cv2.circle(image, (x, y), 1, (0, 255, 0), -1)  # Draw a green circle
            file1.write(str(x)+";"+str(y))
            file1.write("\n")

# Save or display the image with landmarks
output_image_path = 'output_image.jpg'
cv2.imwrite(output_image_path, image)

# Release resources
face_mesh.close()
