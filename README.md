# programming-for-engineers-EPFL
Programming project using LabVIEW, MATLAB and C++ for the course 'Programming for Engineers' (Prof. Salzmann) @ EPF Lausanne
The project more than fulfilled all the requirements and was graded with grade 6/6.

## Project description

The task consisted in the analysis of a video of an air hockey table with pucks, in order to determine the number of impacts between the pucks and the air hockey table as well as the number of impacts between the pucks themselves. A PDF file "AH_score" with the analysis of the game is then produced showing the results.

This project aimed at familiarizing with the three environments (LabVIEW, MATLAB and C++) studied in this class, meant as a general introduction to programming. Each environment manages one stage of the project, therefore the project is divided into several parts schematized by the figure below:

<p align="center">
  <img src=https://github.com/ischollETH/programming-for-engineers-EPFL/blob/main/images/Setup.PNG width="750" title="Setup of the project">
</p>

While LabVIEW is used for the user interface (UI) and to connect all parts, the C++ part tracks the pucks in the frames. A frame sequence is shown in the following:

<p align="center">
  <img src=https://github.com/ischollETH/programming-for-engineers-EPFL/blob/main/images/Seq2m.gif width="750" title="Frame sequence of pucks on the air hockey table">
</p>

Finally, MATLAB is used to evaluate the impacts and to generate the corresponding score and schematic which can be seen in the following:

<p align="center">
  <img src=https://github.com/ischollETH/programming-for-engineers-EPFL/blob/main/images/Seq2m_Result.PNG width="750" title="Resulting graph with puck movements and impacts">
</p>
