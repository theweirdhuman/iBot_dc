import torch
import torch.nn as nn
from torchvision import datasets, transforms, models
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import confusion_matrix
import seaborn as sns

# --------------------
# Transforms (same as val)
# --------------------

val_transforms = transforms.Compose([
    transforms.Resize(256),
    transforms.CenterCrop(224),
    transforms.ToTensor(),
    transforms.Normalize(
        [0.485, 0.456, 0.406],
        [0.229, 0.224, 0.225]
    )
])

# --------------------
# Load Test Dataset
# --------------------

test_dataset = datasets.ImageFolder(
    'data/test',
    transform=val_transforms
)

test_loader = DataLoader(
    test_dataset,
    batch_size=32,
    shuffle=False
)

# --------------------
# Model Setup
# --------------------

model = models.resnet18(
    weights=models.ResNet18_Weights.IMAGENET1K_V1
)

num_features = model.fc.in_features
model.fc = nn.Linear(num_features, 2)

device = torch.device(
    'cuda' if torch.cuda.is_available() else 'cpu'
)
model = model.to(device)

model.load_state_dict(
    torch.load('best_model.pth', map_location=device)
)

model.eval()

# --------------------
# Evaluation Loop
# --------------------

correct = 0
total = 0
all_preds = []
all_labels = []

with torch.no_grad():
    for images, labels in test_loader:
        images = images.to(device)
        labels = labels.to(device)

        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)

        total += labels.size(0)
        correct += (predicted == labels).sum().item()
        all_preds.extend(predicted.cpu().numpy())
        all_labels.extend(labels.cpu().numpy())

test_accuracy = 100 * correct / total
print(f'Test Accuracy: {test_accuracy:.2f}%')

# --------------------
# Confusion Matrix
# --------------------

class_names = ['cats', 'dogs']


cm = confusion_matrix(all_labels, all_preds)
plt.figure(figsize=(6,5))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=class_names, yticklabels=class_names)
plt.xlabel('Predicted Label')
plt.ylabel('Actual Label')
plt.title('Confusion Matrix (Test Set)')
plt.tight_layout()
plt.savefig('confusion_matrix.png')
plt.show()


# --------------------
# Show 5 correct & 5 incorrect predictions
# --------------------


correct_examples = []
incorrect_examples = []

class_names = test_dataset.classes

with torch.no_grad():
    for images, labels in test_loader:
        images = images.to(device)
        labels = labels.to(device)

        outputs = model(images)
        _, preds = torch.max(outputs, 1)

        for i in range(images.size(0)):
            img = images[i].cpu()
            label = labels[i].cpu()
            pred = preds[i].cpu()

            if pred == label and len(correct_examples) < 5:
                correct_examples.append((img, label, pred))
            elif pred != label and len(incorrect_examples) < 5:
                incorrect_examples.append((img, label, pred))

            if len(correct_examples) == 5 and len(incorrect_examples) == 5:
                break
        if len(correct_examples) == 5 and len(incorrect_examples) == 5:
            break


def show_examples(examples, title):
    plt.figure(figsize=(10, 4))
    for i, (img, label, pred) in enumerate(examples):
        img = img.permute(1, 2, 0)
        img = img * torch.tensor([0.229, 0.224, 0.225]) + \
              torch.tensor([0.485, 0.456, 0.406])
        img = img.clamp(0, 1)

        plt.subplot(1, 5, i + 1)
        plt.imshow(img)
        plt.title(f"T:{class_names[label]}\nP:{class_names[pred]}")
        plt.axis("off")

    plt.suptitle(title)
    plt.show()


def show_correct_and_incorrect(correct, incorrect):
    plt.figure(figsize=(15, 6))

    # ----- Correct predictions (top row) -----
    for i, (img, label, pred) in enumerate(correct):
        img = img.permute(1, 2, 0)
        img = img * torch.tensor([0.229, 0.224, 0.225]) + \
              torch.tensor([0.485, 0.456, 0.406])
        img = img.clamp(0, 1)

        plt.subplot(2, 5, i + 1)
        plt.imshow(img)
        plt.title(f"✔ T:{class_names[label]}\nP:{class_names[pred]}")
        plt.axis("off")

    # ----- Incorrect predictions (bottom row) -----
    for i, (img, label, pred) in enumerate(incorrect):
        img = img.permute(1, 2, 0)
        img = img * torch.tensor([0.229, 0.224, 0.225]) + \
              torch.tensor([0.485, 0.456, 0.406])
        img = img.clamp(0, 1)

        plt.subplot(2, 5, i + 6)
        plt.imshow(img)
        plt.title(f"✘ T:{class_names[label]}\nP:{class_names[pred]}")
        plt.axis("off")

    plt.suptitle("Correct (Top) and Incorrect (Bottom) Predictions", fontsize=14)
    plt.tight_layout()
    plt.show()


show_correct_and_incorrect(correct_examples, incorrect_examples)
