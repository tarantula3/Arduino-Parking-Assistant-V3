-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `Arduino`
-- --------------------------------------------------------
-- Table structure for table `Garage`
--

CREATE TABLE `Garage` (
  `ID_` int(11) NOT NULL,
  `Distance` int(11) NOT NULL COMMENT 'Distance of the car from the wall',
  `DateTime` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `Garage`
INSERT INTO `Garage` (`ID_`, `Distance`, `DateTime`) VALUES
(1, 16, 1756026672),
(2, 17, 1756026719),
(3, 9, 1756026758),
(4, 17, 1756026781),
(5, 20, 1756027957),
(6, 16, 1756027980),
(8, 17, 1756028116),
(13, 19, 1756029403),
(15, 18, 1756029643);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Garage`
ALTER TABLE `Garage`
  ADD PRIMARY KEY (`ID_`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Garage`
ALTER TABLE `Garage`
  MODIFY `ID_` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
