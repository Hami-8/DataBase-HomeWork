-- 七张表
-- 	   Customer(customer_id, username, password, phone, nick)
--     Orders(order_id, customer_id, merchant_id, order_date, state, delivery_way, total_money)
--     DishInOrder(order_id, dish_id, count)
--     Dish(dish_id, name, price, category_id, quantity)
--     Category(category_id, name)
--     Merchant(merchant_id, name, address, opening_hours, distance)
--     DishInMerchant(dish_id, merchant_id)

-- 创建并选择数据库
DROP DATABASE IF EXISTS db_test;
CREATE DATABASE db_test;
USE db_test;

-- 设置必要的SQL模式
-- SET sql_mode = 'STRICT_TRANS_TABLES,NO_ENGINE_SUBSTITUTION';

-- 删除已有的表
DROP TABLE IF EXISTS DishInOrder;
DROP TABLE IF EXISTS Orders;
DROP TABLE IF EXISTS DishInMerchant;
DROP TABLE IF EXISTS Dish;
DROP TABLE IF EXISTS Merchant;
DROP TABLE IF EXISTS Customer;
DROP TABLE IF EXISTS Category;

-- 建表语句
CREATE TABLE Customer (
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) NOT NULL,
    password VARCHAR(50) NOT NULL,
    phone VARCHAR(20) NOT NULL,
    nick VARCHAR(50)
);

CREATE TABLE Category (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL
);

CREATE TABLE Merchant (
    merchant_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    address VARCHAR(255) NOT NULL,
    opening_hours VARCHAR(100),
    distance DECIMAL(10, 2)
);

CREATE TABLE Dish (
    dish_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    category_id INT,
    quantity INT,
    FOREIGN KEY (category_id) REFERENCES Category(category_id)
);

CREATE TABLE Orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT,
    merchant_id INT,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    state BOOLEAN,
    delivery_way BOOLEAN,
    total_money DECIMAL(10, 2),
    FOREIGN KEY (customer_id) REFERENCES Customer(customer_id),
    FOREIGN KEY (merchant_id) REFERENCES Merchant(merchant_id)
);

CREATE TABLE DishInOrder (
    order_id INT,
    dish_id INT,
    count INT,
    PRIMARY KEY (order_id, dish_id),
    FOREIGN KEY (order_id) REFERENCES Orders(order_id),
    FOREIGN KEY (dish_id) REFERENCES Dish(dish_id)
);

CREATE TABLE DishInMerchant (
    dish_id INT,
    merchant_id INT,
    PRIMARY KEY (dish_id, merchant_id),
    FOREIGN KEY (dish_id) REFERENCES Dish(dish_id),
    FOREIGN KEY (merchant_id) REFERENCES Merchant(merchant_id)
);

-- 插入数据

INSERT INTO Category (name)
VALUES ('醇香奶茶'),
       ('真鲜果茶');

INSERT INTO Merchant (name, address, opening_hours, distance)
VALUES ('蜜雪冰城南开大学店', '南开大学', '8:00-22:00', 1.5),
       ('蜜雪冰城天津大学店', '天津大学', '9:00-21:00', 2.6);

INSERT INTO Customer (username, password, phone, nick)
VALUES ('hami', '123456', '19154652310', 'haha');

INSERT INTO Dish (name, price, category_id, quantity)
VALUES ('椰果奶茶', 7.00, 1, 166),
       ('芋圆葡萄', 8.9, 2, 80),
       ('珍珠奶茶', 6.6, 1, 120);

INSERT INTO Orders (customer_id, merchant_id, state, delivery_way, total_money)
VALUES (1, 1, 1, 1, 15.9);

INSERT INTO DishInOrder (order_id, dish_id, count)
VALUES (1, 1, 1),
       (1, 2, 1);

INSERT INTO DishInMerchant (dish_id, merchant_id)
VALUES (1, 1),
       (2, 1),
       (3, 1),
       (1, 2);
