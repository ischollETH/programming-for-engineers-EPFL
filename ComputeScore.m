%% © by M. ZEMP & I.SCHOLL GM BA 2

Seq='Seq2m';
Pause=5;
C0=[0.000000 0.623529 0.054902];
C1=[0.137255 0.070588 1.000000];
X1=[57	180	334	486	564	451	336	219	132	39	116	155	237	309	381	448	510	542	560	517	473	428	390	278	163	48	124	227	277	388	489	561	471	387	346	257	170	88	33	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1];
Y1=[54	144	221	289	244	186	127	64	42	89	157	188	252	293	244	203	160	141	121	138	152	166	173	141	107	72	71	68	69	71	72	75	89	106	114	132	149	164	175	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1];

X2=[-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	98	220	429	567	470	412	377	333	290	246	203	184	140	101	63	36	62	73	100	122	148	175	187	212	239	267	293	319	334	356	379	404	426	449	460	483	503	525	547	558	570	551	534	516	498	489	473	454	438	419	402	393	377	359	343	325	313	296	283	270	254	239	234	221	208	193	183	170	164	149	137	126	114	108	95	84	72	61	48	41	34];
Y2=[-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	75	176	292	249	207	184	186	190	195	198	200	201	205	209	212	213	222	227	234	240	247	257	261	267	275	285	292	297	290	288	281	276	270	265	263	257	251	248	242	240	233	220	207	195	181	173	159	147	133	121	106	99	85	72	59	46	37	32	40	47	55	62	66	74	81	89	95	103	105	112	117	124	130	133	139	146	151	158	163	166	171];

%% DISTANCES

X1diff=diff(X1); %calculates difference between two neighboring points 
Y1diff=diff(Y1); %(in both directions for both pucks)
X2diff=diff(X2);
Y2diff=diff(Y2);

distX=X1-X2; %calculates distance between pucks at each moment
distY=Y1-Y2; %(in both directions)


%% NEGATIVE VALUES

vuzX1=find(X1<0); %"values under zero" (vuz) of X1
vuzY1=find(Y1<0); %"values under zero" (vuz) of Y1
vuzX2=find(X2<0); %"values under zero" (vuz) of X1
vuzY2=find(Y2<0); %"values under zero" (vuz) of X1
 
X1(vuzX1)=NaN; %eliminates all values of X1 under zero
Y1(vuzY1)=NaN; %(same for Y1,X2&Y2)
X2(vuzX2)=NaN;
Y2(vuzY2)=NaN;


%% MIN/MAX VALUES

Xmin=min([X1 X2]); %calculates minimal and maximal value in each direction
Xmax=max([X1 X2]);
Ymin=min([Y1 Y2]);
Ymax=max([Y1 Y2]);


%% BORDER REBOUNDS

rB=15;

rebX1max=find(X1+rB>=Xmax); % calculates rebounds with right border of puck 1
CtrlX1max=[0 rebX1max];
CtrlX1max=([rebX1max 0]-CtrlX1max==1);
CtrlX1max(end)=[];
rebX1max=rebX1max-rebX1max.*CtrlX1max;
rebX1max(find(rebX1max==0))=[];

rebX1min=find(X1-rB<=Xmin); % calculates rebounds with left border of puck 1
CtrlX1min=[0 rebX1min];
CtrlX1min=([rebX1min 0]-CtrlX1min==1);
CtrlX1min(end)=[];
rebX1min=rebX1min-rebX1min.*CtrlX1min;
rebX1min(find(rebX1min==0))=[];

rebY1max=find(Y1+rB>=Ymax); % calculates rebounds with top border of puck 1
CtrlY1max=[0 rebY1max];
CtrlY1max=([rebY1max 0]-CtrlY1max==1);
CtrlY1max(end)=[];
rebY1max=rebY1max-rebY1max.*CtrlY1max;
rebY1max(find(rebY1max==0))=[];

rebY1min=find(Y1-rB<=Ymin); % calculates rebounds with bottom border of puck 1
CtrlY1min=[0 rebY1min];
CtrlY1min=([rebY1min 0]-CtrlY1min==1);
CtrlY1min(end)=[];
rebY1min=rebY1min-rebY1min.*CtrlY1min;
rebY1min(find(rebY1min==0))=[];


rebX2max=find(X2+rB>=Xmax); % calculates rebounds with right border of puck 2
CtrlX2max=[0 rebX2max];
CtrlX2max=([rebX2max 0]-CtrlX2max==1);
CtrlX2max(end)=[];
rebX2max=rebX2max-rebX2max.*CtrlX2max;
rebX2max(find(rebX2max==0))=[];

rebX2min=find(X2-rB<=Xmin); % calculates rebounds with left border of puck 2
CtrlX2min=[0 rebX2min];
CtrlX2min=([rebX2min 0]-CtrlX2min==1);
CtrlX2min(end)=[];
rebX2min=rebX2min-rebX2min.*CtrlX2min;
rebX2min(find(rebX2min==0))=[];

rebY2max=find(Y2+rB>=Ymax); % calculates rebounds with top border of puck 2
CtrlY2max=[0 rebY2max];
CtrlY2max=([rebY2max 0]-CtrlY2max==1);
CtrlY2max(end)=[];
rebY2max=rebY2max-rebY2max.*CtrlY2max;
rebY2max(find(rebY2max==0))=[];

rebY2min=find(Y2-rB<=Ymin); % calculates rebounds with bottom border of puck 2
CtrlY2min=[0 rebY2min];
CtrlY2min=([rebY2min 0]-CtrlY2min==1);
CtrlY2min(end)=[];
rebY2min=rebY2min-rebY2min.*CtrlY2min;
rebY2min(find(rebY2min==0))=[];


%% PUCK COLLISIONS

Dmin=50; %settings for collision
alphamin=1;
pos=1:length(X1);

P1ang1=atan2(Y1diff,X1diff); %calculates angle of movement of puck 1
P1ang2=[0 P1ang1];
P1ang2(end)=[];
P1ang3=abs(P1ang2-P1ang1);

 
pos(find(P1ang3<alphamin))=0; %finds all puck collisions
pos(find(sqrt(distX.^2.+distY.^2)>Dmin))=0;
pos(intersect(pos,find(Y1+rB>=Ymax)))=0; %eliminates rebound positions
pos(intersect(pos,find(Y2+rB>=Ymax)))=0;
pos(intersect(pos,find(X1+rB>=Xmax)))=0;
pos(intersect(pos,find(X2+rB>=Xmax)))=0;
pos(intersect(pos,find(Y1-rB<=Ymin)))=0;
pos(intersect(pos,find(Y2-rB<=Ymin)))=0;
pos(intersect(pos,find(X1-rB<=Xmin)))=0;
pos(intersect(pos,find(X2-rB<=Xmin)))=0;

pos(find(pos==0))=[];


%% PLOTTING

figure(); %starts plotting of graphs
hold on; 
axis([-10 615 -50 440]); %sets axes
daspect([1.2 1 1]); %sets ratio between data steps on axes
rectangle('Position',[Xmin Ymin Xmax-Xmin Ymax-Ymin]); %creates borders of AirHockey-table
P1=plot(X1,Y1,'-','LineWidth',1); %plots the graph for Puck 1
P2=plot(X2,Y2,'-','LineWidth',1); %plots the graph for Puck 2
set(P1,'Marker','.','MarkerSize',17,'Color',C0); %sets properties of Puck 1's graph
set(P2,'Marker','.','MarkerSize',17,'Color',C1); %sets properties of Puck 2's graph

title('Air Hockey','FontSize',20); %writes title

rebP1=scatter(X1(rebX1max),Y1(rebX1max),100,'MarkerEdgeColor',C0); % plots all collisions with borders
scatter(X1(rebX1min),Y1(rebX1min),100,'MarkerEdgeColor',C0);
scatter(X1(rebY1max),Y1(rebY1max),100,'MarkerEdgeColor',C0); 
scatter(X1(rebY1min),Y1(rebY1min),100,'MarkerEdgeColor',C0);
rebP2=scatter(X2(rebX2max),Y2(rebX2max),100,'MarkerEdgeColor',C1); 
scatter(X2(rebX2min),Y2(rebX2min),100,'MarkerEdgeColor',C1);
scatter(X2(rebY2max),Y2(rebY2max),100,'MarkerEdgeColor',C1); 
scatter(X2(rebY2min),Y2(rebY2min),100,'MarkerEdgeColor',C1);

coll=scatter(X1(pos),Y1(pos),400,'r','MarkerFaceColor','r','MarkerFaceAlpha',0.2); %,'MarkerSize',11,'MarkerEdgeColor','r','MarkerFaceColor','r','LineWidth',2); % plots puck collisions
scatter(X2(pos),Y2(pos),400,'r','MarkerFaceColor','r','MarkerFaceAlpha',0.2);


d = datetime('now'); %writes current date&time
text(130,330,string(d));    

BTP1=length(rebX1max)+length(rebX1min)+length(rebY1max)+length(rebY1min); %writes number of rebounds of puck 1
BTP1Str=strcat(string(BTP1),' band(s) touched by puck 1');
text(40,15,BTP1Str);

BTP2=length(rebX2max)+length(rebX2min)+length(rebY2max)+length(rebY2min); %writes number of rebounds of puck 2
BTP2Str=strcat(string(BTP2),' band(s) touched by puck 2');
text(40,-5,BTP2Str);

NrCol=length(pos); %writes number of puck collisions
ColStr=strcat(string(NrCol),' puck collision(s)');
text(40,-25,ColStr);

text(40,330,Seq); %writes sequence name

text(400,-25,'© by M.Zemp, I. Scholl GM BA2','FontSize',6) % writes authors names

legend([P1 P2 rebP1 rebP2 coll],'puck 1','puck 2','rebound puck 1','rebound puck 2','puck collision'); %creates graphic's legend
legend('boxoff'); %takes away frame from legend box

hold off;


%% DISPLAYING AND SAVING

pause(Pause);

saveas(gcf,'AH_score.pdf','pdf'); %saves plot as PDF document