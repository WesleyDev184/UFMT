from flask import Flask, render_template, request, flash, redirect
from flask_sqlalchemy import SQLAlchemy
import os

basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///'+os.path.join(basedir,'data.sqlite')
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'chave ultra secreta'
db = SQLAlchemy(app)
    
class Product(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name_prod = db.Column(db.String(64), unique=True, index=True)
    marca = db.Column(db.String(64))
    value = db.Column(db.Float)

    def __repr__(self):
        return '<Product %r>' % self.name_prod

@app.route('/')
def home_page():
    return render_template('index.html')

@app.shell_context_processor
def make_shell_context():
    return dict(db=db, Product=Product)

@app.route('/cadastro')
def form_page():
    return render_template('form.html')

@app.route('/cadastro_form' ,methods=['POST'])
def route_cad():
    db.create_all()

    name = request.form['name']
    marca = request.form['marca']
    valor = request.form['valor']

    product = Product.query.filter_by(name_prod=name).first()
    
    if product is None:
            product = product = Product(name_prod=name,marca=marca,value=valor)
            db.session.add(product)
            db.session.commit()
            flash('Produto inserido com sucesso!','success')
            return redirect('http://127.0.0.1:5000/cadastro')
    else:
         flash('Produto já existe!','info')
         return redirect('http://127.0.0.1:5000')

@app.route('/list')
def list():
    lista = Product.query.all()
    return render_template('list.html',list=lista)

@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

@app.errorhandler(500)
def internal_server_error(e):
    return render_template('500.html'), 500

    
if __name__ == '__main__':
    app.run(debug=True)