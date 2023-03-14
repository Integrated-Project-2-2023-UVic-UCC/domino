import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPainter,QPen,QPixmap

class MainWindow(QtWidgets.QMainWindow):

    def __init__(self):
        super().__init__()

        self.label = QtWidgets.QLabel()
        canvas = QPixmap(500, 500)
        canvas.fill(Qt.white)
        self.label.setPixmap(canvas)
        self.setCentralWidget(self.label)

        self.last_x, self.last_y = None, None

    def mouseMoveEvent(self, e):
        Error= False
        if self.last_x is None: # First event.
            self.last_x = e.x()
            self.last_y = e.y()
            
            return # Ignore the first time.
        
        
        
       
        

        # Update the origin for next time.
        self.last_x = e.x()
        self.last_y = e.y()
        
        if [self.last_x,self.last_y] in llista:
           
            print('Error')
            Error=True
            
        if Error== False:
            painter = QPainter(self.label.pixmap())
            pen=QPen(Qt.black)
            pen.setWidth(5)
            painter.setPen(pen)
            painter.drawLine(self.last_x, self.last_y, e.x(), e.y())
            llista.append([self.last_x,self.last_y])
        painter.end()
        self.update()
        
       
            
            
    def mouseReleaseEvent(self, e):
        self.last_x = None
        self.last_y = None
        print (llista)
        
        

    
        

        
        


llista=[[],[]]
app = QtWidgets.QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()
