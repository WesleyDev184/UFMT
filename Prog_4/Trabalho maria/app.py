from flask import Flask, render_template, request, redirect, url_for, flash, request, jsonify
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, UserMixin, login_user, login_required, logout_user, current_user
from werkzeug.security import generate_password_hash, check_password_hash
import requests

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///site.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'your_secret_key'
db = SQLAlchemy(app)
login_manager = LoginManager(app)
login_manager.login_view = 'login'

favorites = db.Table('favorites',
    db.Column('user_id', db.Integer, db.ForeignKey('user.id'), primary_key=True),
    db.Column('film_id', db.Integer, db.ForeignKey('film.id'), primary_key=True)
)

class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(150), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password = db.Column(db.String(60), nullable=False)
    favorite_films = db.relationship('Film', secondary=favorites, backref=db.backref('favorited_by', lazy='dynamic'))

    def __repr__(self):
        return f"User('{self.username}', '{self.email}')"

class Film(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    year = db.Column(db.String(100), nullable=False)
    actor = db.Column(db.String(100), nullable=False)
    image_url = db.Column(db.String(200), nullable=True)

    def __repr__(self):
        return f'<Film {self.name}>'

@login_manager.user_loader
def load_user(user_id):
    return db.session.get(User, int(user_id))

@app.route('/')
def home():
    films = Film.query.all()
    return render_template('index.html', user=current_user, films=films)

@app.route('/profile')
@login_required
def profile():
    return render_template('profile.html', user=current_user)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('home'))
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user and check_password_hash(user.password, password):
            login_user(user)
            flash('Login successful!', 'success')
            return redirect(url_for('home'))
        else:
            flash('Login unsuccessful. Please check username and password', 'danger')
    return render_template('login.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if current_user.is_authenticated:
        return redirect(url_for('home'))
    if request.method == 'POST':
        username = request.form['username']
        email = request.form['email']
        password = request.form['password']
        existing_user = User.query.filter_by(username=username).first()
        if existing_user is None:
            hashed_password = generate_password_hash(password, method='pbkdf2:sha256')
            user = User(username=username, email=email, password=hashed_password)
            db.session.add(user)
            db.session.commit()
            flash('Registration successful!', 'success')
            return redirect(url_for('login'))
        else:
            flash('Username already exists. Please choose a different one.', 'danger')
    return render_template('register.html')

@app.route('/logout')
@login_required
def logout():
    logout_user()
    flash('You have been logged out.', 'success')
    return redirect(url_for('home'))

@app.route('/toggle_favorite/<int:film_id>', methods=['POST'])
@login_required
def toggle_favorite(film_id):
    film = Film.query.get_or_404(film_id)
    if film in current_user.favorite_films:
        current_user.favorite_films.remove(film)
        db.session.commit()
        return jsonify({'message': f'Removed {film.name} from your favorites.'})
    else:
        current_user.favorite_films.append(film)
        db.session.commit()
        return jsonify({'message': f'Added {film.name} to your favorites.'})

@app.route('/film', methods=['POST'])
def get_film_info():
    film_name = request.form.get('film')
    if not film_name:
        return jsonify({'error': 'Filme não encontrado.'}), 400

    # Verificando se o filme já existe no banco de dados
    existing_films = Film.query.filter(Film.name.ilike(f'%{film_name}%')).all()
    
    if existing_films:
        films_info = [{
            'id': film.id,
            'title': film.name,
            'year': film.year,
            'actors': film.actor,
            'poster': film.image_url
        } for film in existing_films]
        
        return jsonify({
            'message': 'Filmes já existem no banco de dados.',
            'films': films_info
        })

    # URL da API (ajuste para o formato correto da sua API)
    api_url = f"https://imdb.iamidiotareyoutoo.com/search?q={film_name}"
    
    try:
        # Requisição à API
        response = requests.get(api_url)
        response.raise_for_status()
    except requests.RequestException as e:
        return jsonify({'error': 'Erro ao buscar informações do filme.'}), 500
    
    # Obtendo a lista "description" retornada pela API
    film_data_list = response.json().get('description', [])
    if not film_data_list:
        return jsonify({'error': 'Filme não encontrado.'}), 404
    
    for film_data in film_data_list:
        # Extraindo as informações do filme do JSON
        film_info = {
            'title': film_data.get('#TITLE', 'N/A'),
            'year': film_data.get('#YEAR', 'N/A'),
            'actors': film_data.get('#ACTORS', 'N/A'),
            'poster': film_data.get('#IMG_POSTER', '')
        }
        
        # Populando o banco de dados com o filme
        new_film = Film(
            name=film_info['title'],
            year=film_info['year'],
            actor=film_info['actors'],
            image_url=film_info['poster']
        )
        db.session.add(new_film)
    
    db.session.commit()

    # buscar os filmes adicionados
    films = Film.query.filter(Film.name.ilike(f'%{film_name}%')).all()
    films_info = [{
        'id': film.id,
        'title': film.name,
        'year': film.year,
        'actors': film.actor,
        'poster': film.image_url
    } for film in films]

    return jsonify({ 'message': 'Informações do filme obtidas com sucesso.', 'films': films_info })

if __name__ == '__main__':
    app.run(debug=True)