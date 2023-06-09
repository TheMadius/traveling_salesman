# EFRS Control & Viewer
EFRS Control&Viewer - ПО предназначенное для просмотра видеопотоков посредством вебсокетов и управление настройками сервера.

## Требования:
Минимальные:

    - Ubuntu 20.04
    - 4 Гб ОЗУ
    - Intel® Core™ i3 3240 (2 ядрами 4 потока)
    - Видеокарта Nvidia 1060 Ti 3 Гб
Рекомендации:

    - Ubuntu 22.04.1
    - 8 Гб ОЗУ
    - Intel® Core™ i5-8300H  (4 ядрами 8 потока)
    - Видеокарта Nvidia 1060 Ti 6 Гб
# Перед запуском

В некоторых случаях необходимо перед запуском установить следующую зависимость:


    sudo apt install libfuse-dev
# Видеостена

Видеостена представляет из себя группу видеопотоков, расположенных на одном экране, предназначенный для наблюдения за обстановкой.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810038562_.png)

## Функции:
- Переход в полноэкранный режим (по нажатию ENTER);
- Отображение событий распознавания;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810110633_.png)

- Отображение событий обнаружения;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810140250_.png)

- Вывод событий в видеопотоке;
- Развернуть поток на весь экран.
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810880467_+++2022-10-03+22-16-28.png)

# Базовые конфигурации 

Предназначены для настройки и взаимодействие с сервером. Функции :

## Информация о сервере
![Вкладка информация о сервере](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664789881422_.png)


На данной вкладке предоставлена информация о сервере:

- Статус соединения 
- Адрес сервера
- Порт сервера
- Дата обновления состояния
- Дата запуска сервера 
- Характеристики сервера(Память, Процессор, Видеокарта)
## Функции на вкладке:
- Подключиться к новому адресу
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664790821137_.png)

- Вывести окно с информацией о событиях на клиенте(логи)(Кнопка Информация)
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664790862665_.png)

- Очистить кэш (Использовать в ситуации неверного отображения фото добавленного человека)
- Сброс статистики (Для обновления счетчики )
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664790893083_.png)

- Зарегистрировать нового пользователя
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664790916440_.png)

- Синхронизация с 1С**(В демонстрационной версии недоступно)**
## Параметры сервера (В демонстрационной версии недоступно)

На данной вкладке можно настроить параметры сервера.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664791062053_.png)

## Функции:
- Задать указанные настройки 
- Сбросить настройки По умолчанию
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664791224118_.png)

****## Видеопоток

Данная вкладка предназначена для просмотра добавленных потоков. Для просмотра потока необходимо выбрать его в выпадающем списке.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664791254945_.png)

## Функции:
- Просмотр видеопотока 
- Удаление видеопотока с сервера
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664799677467_.png)

****## Добавление видеопотоков 
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664799717039_.png)


На данной вкладке можно добавить видеопоток на сервер. При успешном добавлении в нижнем правом углу появится сообщение о изменении видеопотоков. 

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664799770714_.png)

****## База лиц
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664799803886_.png)


Данная вкладка предназначена для просмотра карточек людей на сервере.

## Функции:
- Отображение фото человека в отдельном форме;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664799829036_.png)

- Отображение маркеров на фотографии;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664799854762_.png)

- Поиск людей по заданному формату;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664799906218_.png)

- Удаление человека из базы;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664802082912_+++2022-10-03+19-31-12.png)

- Редактирование карточки человека;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800386237_.png)

- Добавление нового дескриптора в базу.
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800421926_.png)

## Закрепление 

На данной вкладке можно закрепить дескриптор лица к видеопотоку. При закреплении в данном потоке производится и распознание данный людей (те кто не закреплены на видеопотоке распознаваться не будут!!!)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800472482_.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800499142_.png)

## Функции:
- Добавить дескриптор на все видеопотоки;
- Убрать или добавить дескриптор на конкретный поток.  
****## Режимы потока

Данная вкладка предназначена для настройки у потока зон и минимального размера дескриптора 

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800529455_.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800554392_.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800577666_.png)

## Функции:
- Добавить зону на видеопоток;
- Удалить зону из видеопотока;
- Очистить нарисованную зону.
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800628687_.png)

- Задать новый размер минимального размера рамки у лица;
- Задать размер минимального размера рамки у лица по умолчанию.
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800601549_.png)

## События и отчеты

Данная вкладка представляет из себя просмотрщик событий. На основе найденный событий можно выгрузить отчет в формате CSV.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800660564_.png)

## Функции:
- Поиск событий по заданным параметрам;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800691450_.png)

- Поиск человека в событиях;
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800718012_.png)

- Создание отчета на основе найденных событий.
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800757784_.png)


**Формат отчет**

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664800807119_.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664801254493_.png)

# Просмотрщик

Для просмотра событий был реализован просмотр фото событий в отдельном редакторе. Для просмотра события в редакторе необходимо ПКМ нажать на фото и выбрать пункт Просмотр.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810900489_+++2022-10-03+22-22-48.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810648222_.png)


В результате откроется редактор фото. 

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810589832_.png)


Который включает в себя следующий функционал:

- Выделение зоны
- Приближение изображения с помощью колесика мыши 
- Обрезать кадр по выделенной части
- Сохранение фотографии
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810674040_.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810914706_+++2022-10-03+22-24-47.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664810925442_+++2022-10-03+22-24-54.png)

# Интерактивная карта

Интерактивная карта предназначена для визуального отображения объектов системы на плане задания. Для включения интерактивной карты необходимо нажать на кнопку Интерактивная карта во вкладке Видеостена. 

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664857024812_image.png)


Пример того как может выгляди карта здания с объектами на ней.


![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664854818578_image.png)

## Функции:

Для создания карты необходимо воспользоваться инструментами находящиеся в верхнем левом углу. Они включают в себя:

-  Включение панели управления объектами
-  Создания новой карты 
-  Загрузки карты из файла (Файлы .emap)
-  Сохранить текущую карту на ПК 
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664854844481_image.png)


Для манипуляции с объектами необходимо использовать верхнюю правую панель. Она включает в себя такие манипуляции:

- Просмотр информации об объекте
- Перемещение объектов
- Изменение размера объекта
- Вращение объекта

Для того чтобы взаимодействовать с объектом необходимо дважды нажать на него.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664854862329_image.png)


**Загрузки карты из файла**

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664854877262_image.png)


**Создание новой карты**

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664854908338_image.png)

## Элементы карты

Элементы карты представляют из себя отображением реальных объектов на план здания. Из этого следует что за каждым объектом карты должен быть закреплен объект из системы EFRS. 
Объекты карты включают в себя:

- Камера
- Видеопоток
- Турникет
- Дверь
- Датчик

На карте также присутствуют объекты предназначенные для взаимодействия с объектами системы, они включают в себя:

- Периметр
- Переходы
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664855056551_+++2022-10-04+10-44-01.png)


Создание элемента камера:

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664855072615_image.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664858104965_image.png)


Создание элемента видеопоток:

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664855087976_image.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664858195576_image.png)


Создание элемента переход:

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664855146636_image.png)

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664858273698_image.png)

## Настройка и удаление объектов

Для настройки объектов необходимо выключить панель управления, где будут перечисленный все объекты находящиеся на карте.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664855263732_image.png)


Для изменения параметров или удаления объектов необходимо нажать ПКМ по объекту в панели. Где в пунктах меню можно:

- Изменить параметры объекта
- Удалить с карты
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664855287647_image.png)


Периметр - это объект карты позволяющий ограничить определенную зону на карте, также сделать кто находиться на территории данного периметра. Для отслеживания, необхоимо в настройках периметра указать какие объекты являются внешними, а какие внутренние.

- **Внешние объекты** - отвечают за обнаружение людей, которые входят в периметр.
- **Внутренние объекты** - отвечают за обнаружение людей, которые выходят из периметра.
![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664855300397_image.png)


Пример периметра в котором находится человек.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664856506859_image.png)


Для периметра так же можно посмотреть более подробную информацию о людях находящиеся в периметре. Также в случаи отсутствии человека в данном периметре, можно его выбрать в списке и удалить с помощью кнопки Удалить.   

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664856522306_image.png)


У камер также есть окно в котором отображаются события произошедшие на данной камере.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664856643395_image.png)


После работы с картой можно сохранить ее структуру в файле.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664856548854_image.png)


И при следующем запуске загрузить ее с ПК.

![](https://paper-attachments.dropbox.com/s_1B7F38B096781F892D1DB21271C637ACD2C3AE3B6EF5C71D7B98F84F7F349BC2_1664856572593_image.png)


