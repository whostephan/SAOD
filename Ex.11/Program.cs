using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Xml;

namespace RegExpLab
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = "Dictionary.xml";
            string orig;

            // Чтение файла
            try
            {
                using (StreamReader sr = new StreamReader(path))
                {
                    orig = sr.ReadToEnd();
                    Console.WriteLine("Длина исходного текста: " + orig.Length);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка чтения файла: \"Dictionary.xml\"\n{0}", ex);
                return;
            }

            // Поиск и исправление дефектов
            // Исправление пустых <main-word> с последующим словом
            Regex re = new Regex(@"<main-word>\s*<\/main-word>\s*(\w[\w\u0301-]*)");
            string transformed = re.Replace(orig, @"<main-word><bold>$1</bold></main-word>");

            // Исправление пустых <main-word> с предшествующим словом
            re = new Regex(@"(\w[\w\u0301-]*)\s*<main-word>\s*<\/main-word>");
            transformed = re.Replace(transformed, @"<main-word><bold>$1</bold></main-word>");

            // Проверка на наличие дефектов
            re = new Regex(@".{0,20}<main-word>\s*<\/main-word>.{0,50}");
            MatchCollection matches = re.Matches(transformed);
            if (matches.Count > 0)
            {
                Console.WriteLine("Найдены аномалии:");
                foreach (Match match in matches)
                {
                    Console.WriteLine("Аномалия: " + match.Value);
                }
            }
            else
            {
                Console.WriteLine("Аномалий не найдено.");
            }

            // Сохранение результата
            try
            {
                using (StreamWriter sw = new StreamWriter(path))
                {
                    sw.Write(transformed);
                }
                Console.WriteLine("Файл успешно сохранен.");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка сохранений в файл: \"{0}\"\n{1}", path, ex);
                return;
            }

            // Проверка корректности XML
            try
            {
                XmlDocument doc = new XmlDocument();
                doc.LoadXml(transformed);
                Console.WriteLine("XML сформирован правильно!");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка в XML: {0}", ex);
            }
        }
    }
}
