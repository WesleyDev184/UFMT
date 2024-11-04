from app import app, db

# Cria um contexto de aplicação
with app.app_context():
    db.create_all()
    print("Banco de dados criado com sucesso!")