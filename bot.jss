const Discord = require('discord.js');
const client = new Discord.Client();
const prefix = '!'; // You can set your desired command prefix

client.on('ready', () => {
    console.log(`Logged in as ${client.user.tag}`);
});

client.on('message', (message) => {
    // Ignore messages from other bots or non-prefix messages
    if (message.author.bot || !message.content.startsWith(prefix)) return;

    // Get the command and arguments from the message
    const args = message.content.slice(prefix.length).trim().split(/ +/);
    const command = args.shift().toLowerCase();

    // Simple ping command
    if (command === 'ping') {
        message.reply('Pong!');
    }

    // Simple hello command
    if (command === 'hello') {
        message.reply('Hello!');
    }
});

// Replace 'YOUR_TOKEN' with your actual bot token
client.login('YOUR_TOKEN');
