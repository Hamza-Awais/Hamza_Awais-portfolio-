CREATE DATABASE GymManagementDB;
USE GymManagementDB;

CREATE TABLE Membership_Plans (
    plan_id INT AUTO_INCREMENT PRIMARY KEY,
    plan_name VARCHAR(50) NOT NULL,
    duration_months INT NOT NULL,
    price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE Members (
    member_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(20),
    join_date DATE NOT NULL,
    plan_id INT,
    FOREIGN KEY (plan_id) REFERENCES Membership_Plans(plan_id) ON DELETE SET NULL
);

CREATE TABLE Trainers (
    trainer_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    specialization VARCHAR(50),
    phone VARCHAR(20)
);

CREATE TABLE Classes (
    class_id INT AUTO_INCREMENT PRIMARY KEY,
    trainer_id INT,
    class_name VARCHAR(50) NOT NULL,
    schedule_time DATETIME NOT NULL,
    room VARCHAR(50),
    FOREIGN KEY (trainer_id) REFERENCES Trainers(trainer_id) ON DELETE CASCADE
);

CREATE TABLE Bookings (
    booking_id INT AUTO_INCREMENT PRIMARY KEY,
    member_id INT,
    class_id INT,
    booking_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (member_id) REFERENCES Members(member_id) ON DELETE CASCADE,
    FOREIGN KEY (class_id) REFERENCES Classes(class_id) ON DELETE CASCADE
);

CREATE TABLE Payments (
    payment_id INT AUTO_INCREMENT PRIMARY KEY,
    member_id INT,
    amount DECIMAL(10, 2) NOT NULL,
    payment_date DATE NOT NULL,
    payment_method VARCHAR(50),
    CHECK (amount > 0),
    FOREIGN KEY (member_id) REFERENCES Members(member_id) ON DELETE CASCADE
);


INSERT INTO Membership_Plans (plan_name, duration_months, price) VALUES 
('Basic Monthly', 1, 30.00), ('Pro Monthly', 1, 50.00), ('Elite Monthly', 1, 80.00),
('Basic Quarterly', 3, 80.00), ('Pro Quarterly', 3, 140.00), ('Elite Quarterly', 3, 220.00),
('Basic Annual', 12, 300.00), ('Pro Annual', 12, 500.00), ('Elite Annual', 12, 800.00),
('Student Pass', 1, 20.00), ('Senior Pass', 1, 15.00), ('Weekend Only', 1, 25.00),
('Early Bird', 1, 35.00), ('Night Owl', 1, 35.00), ('Family Plan', 1, 120.00),
('Couples Plan', 1, 80.00), ('Corporate Basic', 12, 250.00), ('Corporate Pro', 12, 450.00),
('Trial Week', 0, 10.00), ('Day Pass', 0, 5.00), ('Basic Bi-Annual', 6, 160.00),
('Pro Bi-Annual', 6, 280.00), ('Elite Bi-Annual', 6, 450.00), ('VIP Lifetime', 120, 5000.00),
('Yoga Only', 1, 40.00), ('Spin Only', 1, 40.00), ('Lifting Only', 1, 40.00),
('Rehab Plan', 3, 100.00), ('Summer Special', 3, 70.00), ('Winter Bulk', 4, 110.00);

INSERT INTO Trainers (name, specialization, phone) VALUES 
('Ali Khan', 'Yoga', '555-0101'), ('Sara Ahmed', 'Spin', '555-0102'), ('John Doe', 'Weightlifting', '555-0103'),
('Mike Smith', 'CrossFit', '555-0104'), ('Emma Watson', 'Pilates', '555-0105'), ('David Lee', 'Boxing', '555-0106'),
('Sophia Chen', 'Yoga', '555-0107'), ('James Bond', 'Agility', '555-0108'), ('Bruce Wayne', 'Martial Arts', '555-0109'),
('Clark Kent', 'Powerlifting', '555-0110'), ('Diana Prince', 'HIIT', '555-0111'), ('Barry Allen', 'Cardio', '555-0112'),
('Arthur Curry', 'Swimming', '555-0113'), ('Victor Stone', 'Rehab', '555-0114'), ('Wanda Maximoff', 'Flexibility', '555-0115'),
('Steve Rogers', 'Endurance', '555-0116'), ('Tony Stark', 'Tech-Fitness', '555-0117'), ('Natasha Romanoff', 'Gymnastics', '555-0118'),
('Clint Barton', 'Accuracy', '555-0119'), ('Sam Wilson', 'Cardio', '555-0120'), ('Bucky Barnes', 'Strength', '555-0121'),
('Scott Lang', 'Mobility', '555-0122'), ('Hope Pym', 'Kickboxing', '555-0123'), ('Stephen Strange', 'Meditation', '555-0124'),
('Peter Parker', 'Agility', '555-0125'), ('Carol Danvers', 'HIIT', '555-0126'), ('Nick Fury', 'Bootcamp', '555-0127'),
('Maria Hill', 'Bootcamp', '555-0128'), ('Phil Coulson', 'General Fitness', '555-0129'), ('Jane Foster', 'Yoga', '555-0130');


INSERT INTO Members (name, email, phone, join_date, plan_id) VALUES 
('Taha Syed', 'taha@mail.com', '123-0001', '2025-01-10', 1), ('Omar Tariq', 'omar@mail.com', '123-0002', '2025-01-12', 2),
('Zainab Ali', 'zainab@mail.com', '123-0003', '2025-01-15', 3), ('Bilal Khan', 'bilal@mail.com', '123-0004', '2025-02-01', 1),
('Aisha Gul', 'aisha@mail.com', '123-0005', '2025-02-10', 8), ('Musa Raza', 'musa@mail.com', '123-0006', '2025-02-14', 10),
('Fatima Noor', 'fatima@mail.com', '123-0007', '2025-03-01', 4), ('Hassan Zia', 'hassan@mail.com', '123-0008', '2025-03-05', 2),
('Usman Beg', 'usman@mail.com', '123-0009', '2025-03-10', 5), ('Iqra Shah', 'iqra@mail.com', '123-0010', '2025-03-20', 11),
('Hamid Mir', 'hamid@mail.com', '123-0011', '2025-04-01', 1), ('Sadia Amin', 'sadia@mail.com', '123-0012', '2025-04-02', 3),
('Kamran Taj', 'kamran@mail.com', '123-0013', '2025-04-10', 7), ('Nida Yasir', 'nida@mail.com', '123-0014', '2025-04-15', 6),
('Adil Qureshi','adil@mail.com', '123-0015', '2025-05-01', 9), ('Sana Javed', 'sana@mail.com', '123-0016', '2025-05-05', 2),
('Fahad Mustafa','fahad@mail.com','123-0017', '2025-05-12', 14),('Mahira Khan','mahira@mail.com','123-0018', '2025-05-20', 16),
('Fawad Khan', 'fawad@mail.com', '123-0019', '2025-06-01', 3), ('Mehwish Hayat','mehwish@mail.com','123-0020','2025-06-05', 4),
('Atif Aslam', 'atif@mail.com', '123-0021', '2025-06-10', 5), ('Ali Zafar', 'aliz@mail.com', '123-0022', '2025-06-15', 8),
('Shafqat A.', 'shafqat@mail.com','123-0023', '2025-07-01', 12), ('Rahat F.', 'rahat@mail.com', '123-0024', '2025-07-02', 15),
('Momina M.', 'momina@mail.com', '123-0025', '2025-07-10', 10),('Asim Azhar', 'asim@mail.com', '123-0026', '2025-07-15', 1),
('Aima Baig', 'aima@mail.com', '123-0027', '2025-08-01', 2), ('Farhan Saeed','farhan@mail.com','123-0028', '2025-08-05', 3),
('Urwa Hocane', 'urwa@mail.com', '123-0029', '2025-08-10', 4), ('Mawra Hocane','mawra@mail.com', '123-0030', '2025-08-15', 5);


INSERT INTO Classes (trainer_id, class_name, schedule_time, room) VALUES 
(1, 'Morning Yoga', '2026-06-15 07:00:00', 'Room A'), (2, 'Spin Intro', '2026-06-15 08:00:00', 'Room B'),
(3, 'Heavy Lifts', '2026-06-15 17:00:00', 'Weight Room'), (4, 'WOD Master', '2026-06-15 18:00:00', 'CrossFit Area'),
(5, 'Core Pilates', '2026-06-16 09:00:00', 'Room A'), (6, 'Boxing Basics', '2026-06-16 10:00:00', 'Ring'),
(7, 'Evening Zen', '2026-06-16 19:00:00', 'Room A'), (8, 'Agility Drills', '2026-06-16 20:00:00', 'Turf'),
(9, 'Kickboxing', '2026-06-17 07:00:00', 'Ring'), (10, 'Power Hour', '2026-06-17 18:00:00', 'Weight Room'),
(11, 'HIIT Burn', '2026-06-17 19:00:00', 'Room B'), (12, 'Treadmill Sprints', '2026-06-18 06:00:00', 'Cardio Deck'),
(13, 'Aqua Aerobics', '2026-06-18 08:00:00', 'Pool'), (14, 'Mobility & Rehab','2026-06-18 10:00:00', 'Room A'),
(15, 'Stretch & Flow', '2026-06-19 07:00:00', 'Room A'), (16, 'Marathon Prep', '2026-06-19 17:00:00', 'Track'),
(17, 'VR Fitness', '2026-06-19 18:00:00', 'Tech Room'), (18, 'Gymnastics 101', '2026-06-20 09:00:00', 'Mat Area'),
(19, 'Target Practice', '2026-06-20 10:00:00', 'Turf'), (20, 'Stairmaster Hell', '2026-06-20 11:00:00', 'Cardio Deck'),
(21, 'Strongman', '2026-06-21 16:00:00', 'Outdoor Area'),(22, 'Joint Health', '2026-06-21 17:00:00', 'Room A'),
(23, 'Muay Thai', '2026-06-22 18:00:00', 'Ring'), (24, 'Mindful Breathing','2026-06-22 19:00:00', 'Room A'),
(25, 'Parkour Basics', '2026-06-23 16:00:00', 'Mat Area'), (26, 'Tabata Protocol', '2026-06-23 17:00:00', 'Room B'),
(27, 'Army Bootcamp', '2026-06-24 06:00:00', 'Turf'), (28, 'Navy Bootcamp', '2026-06-24 07:00:00', 'Turf'),
(29, 'Fit for Life', '2026-06-25 08:00:00', 'Room B'), (30, 'Vinyasa Yoga', '2026-06-25 09:00:00', 'Room A');

INSERT INTO Bookings (member_id, class_id, booking_date) VALUES 
(1, 1, '2026-06-10 10:00:00'), (2, 2, '2026-06-10 10:05:00'), (3, 3, '2026-06-10 10:10:00'),
(4, 4, '2026-06-11 09:00:00'), (5, 5, '2026-06-11 09:15:00'), (6, 6, '2026-06-11 09:30:00'),
(7, 7, '2026-06-12 14:00:00'), (8, 8, '2026-06-12 14:20:00'), (9, 9, '2026-06-12 14:45:00'),
(10, 10, '2026-06-13 11:00:00'),(11, 11, '2026-06-13 11:30:00'),(12, 12, '2026-06-13 12:00:00'),
(13, 13, '2026-06-14 08:00:00'),(14, 14, '2026-06-14 08:30:00'),(15, 15, '2026-06-14 09:00:00'),
(16, 16, '2026-06-15 07:00:00'),(17, 17, '2026-06-15 07:15:00'),(18, 18, '2026-06-15 07:45:00'),
(19, 19, '2026-06-16 10:00:00'),(20, 20, '2026-06-16 10:30:00'),(21, 21, '2026-06-16 11:00:00'),
(22, 22, '2026-06-17 13:00:00'),(23, 23, '2026-06-17 13:20:00'),(24, 24, '2026-06-17 13:40:00'),
(25, 25, '2026-06-18 15:00:00'),(26, 26, '2026-06-18 15:15:00'),(27, 27, '2026-06-18 15:30:00'),
(28, 28, '2026-06-19 16:00:00'),(29, 29, '2026-06-19 16:45:00'),(30, 30, '2026-06-19 17:00:00');

INSERT INTO Payments (member_id, amount, payment_date, payment_method) VALUES 
(1, 30.00, '2026-01-10', 'Credit Card'), (2, 50.00, '2026-01-12', 'Cash'),
(3, 80.00, '2026-01-15', 'Debit Card'),  (4, 30.00, '2026-02-01', 'Credit Card'),
(5, 500.00, '2026-02-10', 'Bank Transfer'),(6, 20.00, '2026-02-14', 'Cash'),
(7, 80.00, '2026-03-01', 'Credit Card'),  (8, 50.00, '2026-03-05', 'Debit Card'),
(9, 140.00, '2026-03-10', 'Credit Card'), (10, 15.00, '2026-03-20', 'Cash'),
(11, 30.00, '2026-04-01', 'Credit Card'), (12, 80.00, '2026-04-02', 'Bank Transfer'),
(13, 300.00, '2026-04-10', 'Credit Card'),(14, 220.00, '2026-04-15', 'Debit Card'),
(15, 800.00, '2026-05-01', 'Bank Transfer'),(16, 50.00, '2026-05-05', 'Credit Card'),
(17, 35.00, '2026-05-12', 'Cash'),        (18, 80.00, '2026-05-20', 'Debit Card'),
(19, 80.00, '2026-06-01', 'Credit Card'), (20, 80.00, '2026-06-05', 'Bank Transfer'),
(21, 140.00, '2026-06-10', 'Credit Card'),(22, 500.00, '2026-06-15', 'Cash'),
(23, 25.00, '2026-07-01', 'Debit Card'),  (24, 120.00, '2026-07-02', 'Credit Card'),
(25, 20.00, '2026-07-10', 'Cash'),        (26, 30.00, '2026-07-15', 'Bank Transfer'),
(27, 50.00, '2026-08-01', 'Credit Card'), (28, 80.00, '2026-08-05', 'Debit Card'),
(29, 80.00, '2026-08-10', 'Cash'),        (30, 140.00, '2026-08-15', 'Credit Card');

INSERT INTO Members (name, email, phone, join_date, plan_id) 
VALUES ('Hamza Awais', 'hamza.awais@mail.com', '123-9999', '2026-06-12', 1);

INSERT INTO Classes (trainer_id, class_name, schedule_time, room) 
VALUES (1, 'Advanced Power Yoga', '2026-06-26 18:00:00', 'Room A');


--    Yeh query Bookings, Members aur Classes ke tables ko aapas mein jor kar 
--    aik clear report banati hai ke kis member ne konsi class kis waqt ke liye book ki hai.

SELECT m.name AS MemberName,c.class_name AS ClassName,c.schedule_time                
FROM Bookings b
JOIN Members m ON b.member_id = m.member_id  
JOIN Classes c ON b.class_id = c.class_id;    



--    Yeh query Payments table mein se har payment method Cash, Card, Bank Transfer 
--    ka total revenue (SUM) aur total transactions (COUNT) nikalti hai or
--   ORDER BY.

SELECT 
    payment_method,                                   
    SUM(amount) AS Total_Revenue,                      
    COUNT(payment_id) AS Number_Of_Transactions       
FROM Payments
GROUP BY payment_method                               
ORDER BY Total_Revenue DESC;                


--    Yahan LEFT JOIN is liye use kiya taake agar kisi plan mein abhi tak koi bhi 
--    member register NAHI hua, toh woh plan bhi list mein show ho aur uske agay 0 likha aaye.

SELECT mp.plan_name, COUNT(m.member_id) AS Total_Members    
FROM Membership_Plans mp
LEFT JOIN Members m ON mp.plan_id = m.plan_id 
GROUP BY mp.plan_name               
ORDER BY Total_Members DESC; 


-- 4

SELECT name 
FROM Members 
WHERE member_id IN (
    SELECT b.member_id 
    FROM Bookings b
    JOIN Classes c ON b.class_id = c.class_id
    JOIN Trainers t ON c.trainer_id = t.trainer_id
    WHERE t.name = 'Ali Khan'
    -- Subquery End
);



-- 5. HAVING CLAUSE: 1 se zyada classes lene wale Trainers
SELECT 
    t.name AS Trainer_Name,       
    COUNT(c.class_id) AS Classes_Taught 
FROM Trainers t
JOIN Classes c ON t.trainer_id = c.trainer_id 
GROUP BY t.trainer_id, t.name   
HAVING COUNT(c.class_id) > 1;       

-- 6. CORRELATED SUBQUERY: Aise payments nikalna jo us payment method ke 
--    AVERAGE amount se zyada hain.Outer query ki line inner query check karegi
 
SELECT p1.payment_id, p1.member_id, p1.amount, p1.payment_method
FROM Payments p1
WHERE p1.amount > (
    SELECT AVG(p2.amount) 
    FROM Payments p2 
    WHERE p2.payment_method = p1.payment_method
);

-- 7. EXISTS Aise Trainers ki list nikalna jinkay paas kam az kam ek class 

SELECT t.trainer_id, t.name, t.specialization
FROM Trainers t
WHERE EXISTS (
    SELECT 1 
    FROM Classes c 
    WHERE c.trainer_id = t.trainer_id
);

-- 8. NOT EXISTS: Aise Members dhoondna jinhon ne abhi tak gym ki koi bhi 
--    class book nahi ki.

SELECT m.member_id, m.name, m.email
FROM Members m
WHERE NOT EXISTS (
    SELECT 1 
    FROM Bookings b 
    WHERE b.member_id = m.member_id
);

-- 9. NESTED JOIN (4 Tables): Ek poori chain banana jahan Member ka naam, 
--    uski booked class, us class ka time aur parhane wale Trainer ka naam aik sath dikhay.

SELECT 
    m.name AS Member_Name, 
    c.class_name AS Class_Name, 
    c.schedule_time AS Class_Time, 
    t.name AS Trainer_Name
FROM Bookings b
JOIN Members m ON b.member_id = m.member_id
JOIN Classes c ON b.class_id = c.class_id
JOIN Trainers t ON c.trainer_id = t.trainer_id;


-- 10. CORRELATED SUBQUERY WITH EXISTS: Aise membership plans dikhana jinko 
--    sirf un members ne khareeda jo 2025 mein register huay thay.

SELECT mp.plan_id, mp.plan_name, mp.price
FROM Membership_Plans mp
WHERE EXISTS (
    SELECT 1 
    FROM Members m 
    WHERE m.plan_id = mp.plan_id 
      AND m.join_date BETWEEN '2025-01-01' AND '2025-12-31'
);



-- 11. 
--    classes se gym ko total kitni kamai (Revenue) hui hai.

SELECT 
    t.name AS Trainer_Name, 
    SUM(member_revenue.total_paid / member_revenue.booking_count) AS Total_Revenue_Generated
FROM (
    SELECT 
        p.member_id, 
        SUM(p.amount) AS total_paid,
        (SELECT COUNT(*) FROM Bookings b WHERE b.member_id = p.member_id) AS booking_count
    FROM Payments p
    GROUP BY p.member_id
) member_revenue
JOIN Bookings b ON member_revenue.member_id = b.member_id
JOIN Classes c ON b.class_id = c.class_id
JOIN Trainers t ON c.trainer_id = t.trainer_id
GROUP BY t.trainer_id, t.name
ORDER BY Total_Revenue_Generated DESC;



-- 12. 

SELECT t.trainer_id, t.name, t.specialization
FROM Trainers t
WHERE NOT EXISTS (
    SELECT 1 
    -- 
    FROM Classes c 
    WHERE c.trainer_id = t.trainer_id 
      AND c.room = 'Room A'
);


-- 13  Un members ke naam aur emails nikalna 
--    jinhon ne aam normal classes ke bajaye 'Yoga' specialization wale trainer ki class book ki.

SELECT DISTINCT m.name AS Yoga_Enthusiast, m.email
FROM Members m
JOIN Bookings b ON m.member_id = b.member_id
JOIN Classes c ON b.class_id = c.class_id
JOIN Trainers t ON c.trainer_id = t.trainer_id
WHERE t.specialization = 'Yoga';



-- 14.Har member ki sab se latest/aakhri 
--    payment ki date aur raqam check karna.

SELECT p1.member_id, p1.amount, p1.payment_date
FROM Payments p1
WHERE p1.payment_date = (
    SELECT MAX(p2.payment_date) 
    FROM Payments p2 
    WHERE p2.member_id = p1.member_id
);
-- 15 Har class ka naam, uske trainer ka naam 
--  aur total bookings count karna, aur sirf wahi classes dikhana jinki booking 0 se zyada hain.

SELECT 
    c.class_name, 
    t.name AS Trainer_Name, 
    COUNT(b.booking_id) AS Total_Seats_Booked
FROM Classes c
JOIN Trainers t ON c.trainer_id = t.trainer_id
LEFT JOIN Bookings b ON c.class_id = b.class_id
GROUP BY c.class_id, c.class_name, t.name
HAVING COUNT(b.booking_id) >= 1
ORDER BY Total_Seats_Booked DESC;


-- 16

SELECT 
    m.name AS Member_Name, 
    mp.plan_name AS Plan_Name, 
    m.join_date AS Join_Date,
    DATE_ADD(m.join_date, INTERVAL mp.duration_months MONTH) AS Expiry_Date
FROM Members m
JOIN Membership_Plans mp ON m.plan_id = mp.plan_id
ORDER BY Expiry_Date;