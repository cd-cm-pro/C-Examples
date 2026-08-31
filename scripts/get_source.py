import requests
print("Wait a seconds...")

vibe_boom = requests.get("https://www.myinstants.com/media/sounds/vine-boom.mp3")
vibe_boom.raise_for_status()
with open("files/vibe-boom.mp3", 'wb') as file:
    for chunk in vibe_boom.iter_content(chunk_size=1024):
        if chunk:
            file.write(chunk)
    
print("Complated")