import cv2
import numpy as np

# 1) Import image lenna.png and display it

# Use the function cv2.imread() to read an image
img = cv2.imread('lenna.png')
# Use the function cv2.imshow() to display an image in a window.
cv2.imshow('image', img)
# cv2.waitKey() The function waits for specified milliseconds for any keyboard event
cv2.waitKey(0)
# cv2.destroyAllWindows() simply destroys all the windows we created.
cv2.destroyAllWindows()

# 2) Display the width, height and the number of color channels of the image
# get dimensions of image
dimensions = img.shape
height = img.shape[0]
width = img.shape[1]
channels = img.shape[2]

print('Image Dimension    : ', dimensions)
print('Image Height       : ', height)
print('Image Width        : ', width)
print('Number of Color Channels : ', channels)

# 3) Convert the image to grayscale and display it
# convert to grayscale
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

cv2.imshow("Grayscale Image", gray)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 4) Resize the image to be 200 px in width and the proportional height using INTER_CUBIC
# interpolation and display it

# get ratio width to its height
ratio = img.shape[1] / img.shape[0]

# Set the new width and calculate the new height
newWidth = 200
newHeight = int(newWidth / ratio)

# Resize the image
img = cv2.resize(gray, (newWidth, newHeight), interpolation=cv2.INTER_CUBIC)

cv2.imshow("Resized Image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 5) Crop Lenna’s face from the resized image
# Define the coordinates of the region containing Lenna's face
x = 50
y = 50
w = 100
h = 100

# Crop the region
cropped_img = img[y:y + h, x:x + w]

cv2.imshow("Cropped Image", cropped_img)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 6) Apply median blur with kernel size 3 to the image from step 5 and display it

# Apply median blur with kernel size 3
median_blur = cv2.medianBlur(cropped_img, 3)
# The median blur function replaces each pixel in the image with the median value of the pixels in its kernel-sized neighborhood.
cv2.imshow("Median Blurred Image", median_blur)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 7) Use Gaussian adaptive threshold and morphological operations to mask the image from step 6
# and display the result
gaussianAdaptiveThreshold = cv2.adaptiveThreshold(median_blur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 9, 6)
cv2.imshow("Gaussian adaptive thereshold",gaussianAdaptiveThreshold)
cv2.waitKey(0)
cv2.destroyAllWindows()


gaussianMaskedImage = cv2.bitwise_and(cropped_img, cropped_img, mask = gaussianAdaptiveThreshold)
cv2.imshow("Guassian Masked Image",gaussianMaskedImage)
cv2.waitKey(0)
cv2.destroyAllWindows()



kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
kW, kH = 3, 3
closing = cv2.morphologyEx(gaussianMaskedImage, cv2.MORPH_CLOSE, kernel)
cv2.imshow("closing",closing)
cv2.waitKey(0)
cv2.destroyAllWindows()



salted_image = closing
height, width = salted_image.shape[:2]
salted_px = 0.03 * salted_image.size

h_pos = np.random.randint(0, height-1, int(salted_px))
w_pos = np.random.randint(0, width-1, int(salted_px))

salted_image[h_pos, w_pos] = 255

pepper = closing
h, w = pepper.shape[:2]
pepper_px = 0.03 * pepper.size

h_pos = np.random.randint(0, height-1, int(pepper_px))
w_pos = np.random.randint(0, width-1, int(pepper_px))

salted_image[h_pos, w_pos] = 0
salted_image[h_pos, w_pos] = 0

cv2.imshow("salted image",salted_image)
cv2.waitKey(0)
cv2.destroyAllWindows()


# 10) Remove the noise from the image from step 9
blurred_lenna = cv2.medianBlur(salted_image, 5)
cv2.imshow("Blurred lenna",blurred_lenna)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 11) Make a negative of the image from step 10 and display it
negative_image = 255 - blurred_lenna
cv2.imshow("Negative image", negative_image)
cv2.waitKey(0)
cv2.destroyAllWindows()


# 12) Use Canny Edge detector to detect edges on the image from step 11 and display it
canny_image = cv2.Canny(negative_image, 80, 160)
cv2.imshow("Canny image", canny_image)
cv2.waitKey(0)
cv2.destroyAllWindows()

kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (39, 39))
kW, kH = 39, 39
edge_image = cv2.morphologyEx(canny_image, cv2.MORPH_BLACKHAT, kernel)
cv2.imshow("Canny Edge image", edge_image)
cv2.waitKey(0)
cv2.destroyAllWindows


cv2.imwrite("/lenna.png", edge_image)













































