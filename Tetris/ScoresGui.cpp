#include "ScoresGui.h"


void ScoresGui::initComp()
{

	setWindowModality(Qt::ApplicationModal);

	vb = new QVBoxLayout();
	this->setLayout(vb);

	table = new QTableWidget();
	table->setColumnCount(2);
	table->setRowCount(10);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);

	table->verticalHeader()->setVisible(false);
	table->horizontalHeader()->setVisible(false);

	vb->addWidget(table);

	
}

void ScoresGui::reloadTable()
{

	auto scores = serv.sortScore();

	table->clear();
	table->setRowCount(scores.size());

	int i = 0;
	for (const auto& sc : scores) {

		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(sc.getName())));
		table->setItem(i, 1, new QTableWidgetItem(QString::number(sc.getScore())));
		i++;

	}

}

ScoresGui::~ScoresGui()
{
}

void ScoresGui::update()
{
	reloadTable();
}

void ScoreInputGui::initComp()
{
	setWindowModality(Qt::ApplicationModal);
	vb = new QVBoxLayout();
	this->setLayout(vb);

	lblScore = new QLabel("Score: "+ QString::number(boardgame.getScore()));
	lblName = new QLabel("Enter your name");
	txtName = new QLineEdit;
	submit = new QPushButton("Submit");

	input = new QWidget();
	fl = new QFormLayout();
	input->setLayout(fl);
	fl->addRow(lblName, txtName);

	vb->addWidget(lblScore);
	vb->addWidget(input);
	vb->addWidget(submit);

}

void ScoreInputGui::connectSlots()
{

	QObject::connect(submit, &QPushButton::clicked, this, &ScoreInputGui::addScore);

}

void ScoreInputGui::addScore()
{

	if (txtName->text().toStdString() != "") {

		serv.saveScore(txtName->text().toStdString(), boardgame.getScore());

		ScoresGui *scores = new ScoresGui(serv);
		scores->show();

		this->close();

	}

}
