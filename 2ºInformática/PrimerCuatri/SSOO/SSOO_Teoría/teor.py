# Load the uploaded PDF file
file_path = '/mnt/data/Tema4Presentacion (4).pdf'
pdf_reader = PdfReader(file_path)

# Extract all the text from the PDF
full_text = ""
for page in pdf_reader.pages:
    full_text += page.extract_text()

# Save the extracted text to a text file for the user
output_file_path = '/mnt/data/Tema4Presentacion_full_text.txt'
with open(output_file_path, 'w', encoding='utf-8') as text_file:
    text_file.write(full_text)

output_file_path
