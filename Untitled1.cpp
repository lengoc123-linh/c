#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Struct đại diện một ảnh
typedef struct Image {
    char name[255];
    char date[11]; // format: DD-MM-YYYY
    char description[255];
    int size; // KB
    struct Image* next;
} Image;


Image* head = NULL;


// Hàm xóa màn hình (dùng system("clear") nếu chạy trên Linux)
void clearScreen() {
    system("cls");
}


// Dừng màn hình để người dùng đọc kết quả
void pause() {
    printf("\nPress Enter to continue...");
    getchar(); // Đọc ký tự Enter
    getchar(); // Đọc lần 2 nếu bị skip
}


// Tạo một ảnh mới
Image* createImage() {
    Image* newImage = (Image*)malloc(sizeof(Image));
    if (!newImage) {
        printf("Memory allocation failed.\n");
        return NULL;
    }


    printf("Enter photo name: ");
    scanf(" %[^\n]", newImage->name);


    printf("Enter date (DD-MM-YYYY): ");
    scanf(" %[^\n]", newImage->date);


    printf("Enter description: ");
    scanf(" %[^\n]", newImage->description);


    printf("Enter size (KB): ");
    scanf("%d", &newImage->size);


    newImage->next = NULL;
    return newImage;
}


// Thêm ảnh vào cuối danh sách
void addPhoto() {
    Image* newImage = createImage();
    if (!newImage) return;


    if (head == NULL) {
        head = newImage;
    } else {
        Image* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newImage;
    }
    printf("\nPhoto added successfully!\n");
    pause();
}


// Hiển thị tất cả ảnh
void displayPhotos() {
    if (head == NULL) {
        printf("No photos in the album.\n");
        pause();
        return;
    }


    printf("\n%-20s %-12s %-10s %s\n", "Photo Name", "Date", "Size(KB)", "Description");
    printf("------------------------------------------------------------------\n");


    Image* temp = head;
    while (temp != NULL) {
        printf("%-20s %-12s %-10d %s\n", temp->name, temp->date, temp->size, temp->description);
        temp = temp->next;
    }
    pause();
}


// Tìm ảnh theo tên
Image* findPhoto(char* name) {
    Image* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}






// Tìm kiếm ảnh
void searchPhoto() {
    char name[100];
    printf("Enter photo name to search: ");
    scanf(" %[^\n]", name);


    Image* photo = findPhoto(name);
    if (photo) {
        printf("\nPhoto found:\n");
        printf("Name: %s\nDate: %s\nSize: %d KB\nDescription: %s\n",
               photo->name, photo->date, photo->size, photo->description);
    } else {
        printf("Photo not found.\n");
    }
    pause();
}


// Xoá ảnh
void deletePhoto() {
    char name[100];
    printf("Enter photo name to delete: ");
    scanf(" %[^\n]", name);


    Image* temp = head;
    Image* prev = NULL;


    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }


    if (temp == NULL) {
        printf("Photo not found.\n");
    } else {
        if (prev == NULL) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("Photo deleted successfully.\n");
    }
    pause();
}


// Sửa ảnh
void editPhoto() {
    char name[100];
    printf("Enter photo name to edit: ");
    scanf(" %[^\n]", name);


    Image* photo = findPhoto(name);
    if (!photo) {
        printf("Photo not found.\n");
        pause();
        return;
    }


    printf("Editing photo: %s\n", name);
    printf("Enter new date (DD-MM-YYYY): ");
    scanf(" %[^\n]", photo->date);


    printf("Enter new description: ");
    scanf(" %[^\n]", photo->description);


    printf("Enter new size (KB): ");
    scanf("%d", &photo->size);


    printf("Photo updated successfully.\n");
    pause();
}


// Phát hiện ảnh trùng
void detectDuplicates() {
    int found = 0;
    Image* ptr1 = head;


    while (ptr1 != NULL) {
        Image* ptr2 = ptr1->next;
        while (ptr2 != NULL) {
            if (strcmp(ptr1->name, ptr2->name) == 0 &&
                strcmp(ptr1->date, ptr2->date) == 0) {
                printf("Duplicate found: %s on %s\n", ptr1->name, ptr1->date);
                found = 1;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }


    if (!found)
        printf("No duplicates found.\n");


    pause();
}
// tat ca deu la ham void, input thi se nhap ben trong ham


// sap xep anh theo name, ngay thang, kich thuoc

void sortImage() {
    int option;
    printf("Sort by:\n1. Name\n2. Date\n3. Size\n=> ");
    scanf("%d", &option);

    for (Image* i = head; i != NULL; i = i->next) {
        for (Image* j = i->next; j != NULL; j = j->next) {
            int shouldSwap = 0;
            if (option == 1 && strcmp(i->name, j->name) > 0) {
                shouldSwap = 1;
            } else if (option == 2 && strcmp(i->date, j->date) > 0) {
                shouldSwap = 1;
            } else if (option == 3 && i->size > j->size) {
                shouldSwap = 1;
            }
            if (shouldSwap) {
                // Hoán đổi nội dung 2 nút
                Image temp = *i;
                *i = *j;
                *j = temp;

                // Cập nhật liên kết next
                Image* tmpNext = i->next;
                i->next = j->next;
                j->next = tmpNext;
            }
        }
    }

    printf("Photos sorted.\n");
    pause();
}





// thong ke anh theo thang nam
//input: nhap vao khong thoi gian: vd 19.9.2003 -> 21.5.2025
//thong ke ra nhung anh thoa man tieu chi

int convertDateToInt(const char* date) {
    int d, m, y;
    sscanf(date, "%d-%d-%d", &d, &m, &y);
    return y * 10000 + m * 100 + d;
}

void static_image_based_on_time() {
    char dateStart[11], dateEnd[11];
    printf("Enter start date (DD-MM-YYYY): ");
    scanf(" %[^\n]", dateStart);
    printf("Enter end date (DD-MM-YYYY): ");
    scanf(" %[^\n]", dateEnd);

    int start = convertDateToInt(dateStart);
    int end = convertDateToInt(dateEnd);

    Image* temp = head;
    int found = 0;
    while (temp != NULL) {
        int photoDate = convertDateToInt(temp->date);
        if (photoDate >= start && photoDate <= end) {
            printf("%s - %s\n", temp->name, temp->date);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) printf("No photos found in the given date range.\n");
    pause();
}


//Tim kiem dua tren cac tieu chi: vi du dua vao ten, dua vao ngay chup
//input: lua chonj option name or time, if name -> nhap name, if time -> nhap time
// output: image thoa man tieu chi
void search_advanced() {
    int option;
    printf("Search by:\n1. Name\n2. Date\n=> ");
    scanf("%d", &option);
    getchar(); // Clear buffer

    if (option == 1) {
        char name[100];
        printf("Enter name: ");
        scanf(" %[^\n]", name);
        Image* img = findPhoto(name);
        if (img) {
            printf("Found: %s - %s\n", img->name, img->date);
        } else {
            printf("Photo not found.\n");
        }
    } else if (option == 2) {
        char date[11];
        printf("Enter date (DD-MM-YYYY): ");
        scanf(" %[^\n]", date);
        Image* temp = head;
        int found = 0;
        while (temp) {
            if (strcmp(temp->date, date) == 0) {
                printf("Found: %s - %s\n", temp->name, temp->description);
                found = 1;
            }
            temp = temp->next;
        }
        if (!found) printf("No photo found with that date.\n");
    } else {
        printf("Invalid option.\n");
    }
    pause();
}


// xuat file txt: nhap thong tin album anh cua minh ra file txt
void export_file() {
    FILE* file = fopen("album.txt", "w");
    if (!file) {
        printf("Cannot open file.\n");
        return;
    }

    Image* temp = head;
    while (temp) {
        fprintf(file, "%s,%s,%d,%s\n", temp->name, temp->date, temp->size, temp->description);
        temp = temp->next;
    }

    fclose(file);
    printf("Exported to album.txt\n");
    pause();
}

//Hoan tac thao tac truoc do
// vd: nhap 1 image -> undo -> quay lai trang thai truoc khi nhap
typedef struct Action {
    Image* snapshot;
    struct Action* next;
} Action;

Action* undoStack = NULL;
Image* copyList(Image* src);
void freeList();
void pushSnapshot() {
    Image* copy = copyList(head);  // <-- Thực sự gọi copyList() để sao chép danh sách
    Action* newAction = (Action*)malloc(sizeof(Action));
    newAction->snapshot = copy;
    newAction->next = undoStack;
    undoStack = newAction;
}


Image* copyList(Image* src) {
    if (!src) return NULL;
    Image* newHead = NULL;
    Image* tail = NULL;
    while (src) {
        Image* newNode = (Image*)malloc(sizeof(Image));
        *newNode = *src;
        newNode->next = NULL;

        if (!newHead) newHead = newNode;
        else tail->next = newNode;
        tail = newNode;

        src = src->next;
    }
    return newHead;
}

void undo() {
    if (!undoStack) {
        printf("No actions to undo.\n");
        pause();
        return;
    }

    freeList(); // Free current list
    head = undoStack->snapshot;

    Action* temp = undoStack;
    undoStack = undoStack->next;
    free(temp);

    printf("Undo successful.\n");
    pause();
}



//dung graph -> luu lien ket giua cac image
// vd cai iamge1,4,6 co chung moi lien ket (cung topic, cung ngay thang,...) -> 1 image = 1 node, lien ket 2 node = edge co weight(trong so)


int countImages() {
    int count = 0;
    Image* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

void buildImageArray(Image** imageArr, int n) {
    Image* temp = head;
    int i = 0;
    while (temp && i < n) {
        imageArr[i++] = temp;
        temp = temp->next;
    }
}
void create_relation_graph() {
    int n = countImages();
    if (n == 0) {
        printf("No photos to analyze.\n");
        pause();
        return;
    }

    Image* images[n];
    buildImageArray(images, n);

    int graph[n][n];
    memset(graph, 0, sizeof(graph));

    // Xây dựng ma trận dựa trên tiêu chí (ví dụ: cùng ngày chụp)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(images[i]->date, images[j]->date) == 0) {
                graph[i][j] = 1;
                graph[j][i] = 1; // Đồ thị vô hướng
            }
        }
    }

    // Hiển thị ma trận kề
    printf("Adjacency Matrix (based on same date):\n\n");

    printf("%10s", "");
    for (int i = 0; i < n; i++) {
        printf("%10d", i);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%10d", i);
        for (int j = 0; j < n; j++) {
            printf("%10d", graph[i][j]);
        }
        printf("\n");
    }

    // Hiển thị bảng ánh xạ index -> tên ảnh
    printf("\nImage Index Mapping:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> %s (%s)\n", i, images[i]->name, images[i]->date);
    }

    pause();
}







// Menu chính
void showMenu() {
    int choice;
    do {
        clearScreen();
        printf("====== Photo Album Manager ======\n");
        printf("1. Add Photo\n");
        printf("2. Delete Photo\n");
        printf("3. Search Photo\n");
        printf("4. Edit Photo\n");
        printf("5. Display All Photos\n");
        printf("6. Detect Duplicates\n");
        printf("0. Exit\n");
        printf("=> Your choice: ");
        scanf("%d", &choice);


        clearScreen();
        switch (choice) {
            case 1: addPhoto(); break;
            case 2: deletePhoto(); break;
            case 3: searchPhoto(); break;
            case 4: editPhoto(); break;
            case 5: displayPhotos(); break;
            case 6: detectDuplicates(); break;
            case 0: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n"); pause(); break;
        }
    } while (choice != 0);
}


// Giải phóng bộ nhớ
void freeList() {
    Image* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


int main() {
    showMenu();
    freeList();
    return 0;
}